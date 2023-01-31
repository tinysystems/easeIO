#include <string>

#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/ParentMap.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/raw_ostream.h"
#include <boost/algorithm/string/replace.hpp>
#include<sstream>


using namespace clang;
using namespace boost;
using namespace clang::ast_matchers;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;
using namespace std;

/*** rewriter for the transformed code***/
Rewriter transfd_code_writer;


/***  Templates for code injection ***/

string flag_decls = "";

string op_name_TS_decls = "__nv bool op_TS[*length*];\n";

int flag_itr = 0,TS_itr=0;

string flag_decl_template = "__nv bool flag[*length*]";

string io_call_single_template = "\tif(!flag[*f_itr*]) { \n\t*op_name*;\n\t flag[*f_itr*] = SET;\n\t}";
string io_call_single_retval_template = "if(!flag[*f_itr*]) { *retval* = *op_name*;\n\t flag[*f_itr*] = SET;\n\t}";

string io_call_always_retval_template = "\n\t*retval* = *op_name*;\n\t";

string io_call_timely_retval_template = "\n\tif(!flag[*f_itr*] && (GetTime() - op_TS[*t_itr*]) < *EXPIRE_TIME*)) {\n\t *retval* = *op_name*;\n\t op_TS[*t_itr*] = GetTime();\n\t *retval*_priv = *retval*;\n\t flag[*f_itr*] = SET;\n\t}\n\t else { \n\t *retval* = *retval*_priv;\n\t }";


string io_call_timely_template = "\n\tif(!flag[*f_itr*] && (GetTime() - op_TS[*t_itr*]) < *EXPIRE_TIME*)) {\n\t *op_name*;\n\t op_TS[*t_itr*] = GetTime();\n\t *retval*_priv = *retval*;\n\t flag[*f_itr*] = SET;\n\t}\n\t else { \n\t*retval* = *retval*_priv;\n\t}";


string io_block_begin_single_template = "\n\tif(!flag[*f_itr*]) { "; 

string io_block_end_single_template = "\n\tflag[*f_itr*] = SET;\n\t}";

string io_block_begin_timely_retval_template = "\n\tif(!flag[*f_itr*] && (GetTime() - op_TS[*t_itr*]) < *EXPIRE_TIME*)) { ";

string io_block_end_timely_retval_template = "\nt op_TS[*t_itr*] = GetTime();\n\t flag[*f_itr*] = SET;\n\t}\n\t";

string private_var_list = "";

string private_var_template = "__nv *type* *var_name*_priv;\n";

string DMA_var_priv_template_if = "\n\t*var_name*_priv = *var_name*;";

string DMA_var_priv_template_else = "\n\t*var_name* = *var_name*_priv;";

string DMA_var_priv_func_start_template = "\n\tif(!DMA_Data.DMA_Privatization[DMACounter-1])\n\t{\n\t*if_template* \n\r\t DMA_Data.DMA_Privatization[DMACounter-1] = COMPLETED;\n\t}\n\t else {\n\t*else_template*\n\t}\n\t ";

string DMA_var_priv_func_end_template = "\n\tif(!DMA_Data.DMA_Privatization[DMACounter-1]){ \n\tDMA_Data.DMA_Privatization[DMACounter-1] = COMPLETED;\n\t} \n\t else {}\n\t ";



typedef struct 
{
   string funcName;
   string variableList[20];
   string datatypes[20];   
   bool isVisited;
   int sizeOfVarList;
}GV_to_Func_Map;

GV_to_Func_Map functionList[20];
int sizeOfFuncList=0;


/* Utility function for replacing the string */
void replaceAll(string &s, const string &search, const string &replace) {
  for (size_t pos = 0;; pos += replace.length()) {
    // Locate the substring to replace
    pos = s.find(search, pos);
    if (pos == string::npos)
      break;
    // Replace by erasing and inserting
    s.erase(pos, search.length());
    s.insert(pos, replace);
  }
}

/*  Semantic Analyzer */
static cl::OptionCategory MatcherSampleCategory("EaseIO-Compiler");


/* AST Matcher for call_IO */


string getAllGlobalVariables(){
   stringstream f_itr,t_itr; string f_temp,t_temp;
   f_itr<<(flag_itr+1);
   f_itr>>f_temp;
   t_itr<<(TS_itr+1);
   t_itr>>t_temp;
  
   string final_res=""; 
   
   if(TS_itr > 0){
     replaceAll(op_name_TS_decls,"*length*",t_temp);
     final_res = final_res + op_name_TS_decls+"\n";
   }
  
   if(flag_itr > 0){
     replaceAll(flag_decl_template,"*length*",f_temp);
     final_res = final_res + flag_decl_template+"\n";
   }
   
   return final_res+"\n"+private_var_list;
}

int extractCallArguments(const CallExpr *call, string *argv){
  int len_of_call = 0;
  int argc = call->getNumArgs();
  LangOptions LangOpts;
  LangOpts.CPlusPlus = true;
  PrintingPolicy Policy(LangOpts);
  string TypeS;
  
  for(int i=0, j = argc; i<j; i++)
    {
        string TypeS;
        raw_string_ostream s(TypeS);
        call->getArg(i)->printPretty(s, 0, Policy);
        argv[i] = s.str();
        len_of_call = len_of_call + argv[i].length();
    }
  
  SourceRange range(call->getBeginLoc(),call->getEndLoc());
  transfd_code_writer.ReplaceText(range, "");
  transfd_code_writer.ReplaceText(call->getEndLoc(), 2 ,"");  // removing semicolon    
 
  int call_length = call->getDirectCallee()->getNameInfo().getName().getAsString().length();
  len_of_call = len_of_call + call->getNumArgs() +  call_length + 3;// two brackets and semicolon

 return len_of_call;
}


void replaceArgumentsInTimelyRetValTemplate(string *argv, string &io_call_timely_retval_template, int size){
   stringstream f_itr,t_itr; string t_temp; string f_temp;
   t_itr<<TS_itr;
   t_itr>>t_temp;
   TS_itr++;

   f_itr<<flag_itr;
   f_itr>>f_temp;
   flag_itr++;

   replaceAll(io_call_timely_retval_template,"*t_itr*",t_temp);
   replaceAll(io_call_timely_retval_template,"*f_itr*",f_temp);
   replaceAll(io_call_timely_retval_template,"*EXPIRE_TIME*",argv[1]);
   replaceAll(io_call_timely_retval_template,"*retval*",argv[2]);
   replaceAll(io_call_timely_retval_template,"*op_name*",argv[3]);
}

void replaceArgumentsInTimelyTemplate(string *argv, string &io_call_timely_retval_template, int size){
   stringstream f_itr,t_itr; string t_temp; string f_temp;
   t_itr<<TS_itr;
   t_itr>>t_temp;
   TS_itr++;

   f_itr<<flag_itr;
   f_itr>>f_temp;
   flag_itr++;

   replaceAll(io_call_timely_retval_template,"*t_itr*",t_temp);
   replaceAll(io_call_timely_retval_template,"*f_itr*",f_temp);
   replaceAll(io_call_timely_retval_template,"*EXPIRE_TIME*",argv[1]);
   replaceAll(io_call_timely_retval_template,"*op_name*",argv[2]);
}


void replaceArgumentsInSingleTemplate(string *argv, string &io_call_single_template, int size){
   stringstream f_itr,t_itr; string f_temp;
   f_itr<<flag_itr;
   f_itr>>f_temp;
   flag_itr++;

   replaceAll(io_call_single_template,"*f_itr*",f_temp);
   replaceAll(io_call_single_template,"*op_name*",argv[1]);
}

void replaceArgumentsInSingleRetValTemplate(string *argv, string &io_call_single_retval_template, int size){
   stringstream itr; string f_temp;

   itr<<flag_itr;
   itr>>f_temp;
   flag_itr++;

   replaceAll(io_call_single_retval_template,"*f_itr*",f_temp);
   replaceAll(io_call_single_retval_template,"*op_name*",argv[2]);
}


void replaceArgumentsInTimelyBlockTemplate(string *argv, string &io_block_begin_timely_retval_template, int size){
    
   stringstream f_itr,t_itr; string t_temp,f_temp;
   t_itr<<TS_itr;
   t_itr>>t_temp;
   TS_itr++;

   f_itr<<flag_itr;
   f_itr>>f_temp;
   flag_itr++;

   replaceAll(io_block_begin_timely_retval_template,"*t_itr*",t_temp);
   replaceAll(io_block_begin_timely_retval_template,"*f_itr*",f_temp);
   replaceAll(io_block_begin_timely_retval_template,"*EXPIRE_TIME*",argv[1]);
} 

void replaceArgumentsInSingleBlockTemplate(string *argv, string &io_block_begin_single_retval_template, string &io_block_end_single_retval_template, int size){
  stringstream itr; string temp;
  itr<<flag_itr;
  itr>>temp;
  flag_itr++;
  replaceAll(io_block_begin_single_retval_template,"*f_itr*",temp);
  replaceAll(io_block_end_single_retval_template,"*f_itr*",temp);
} 

string io_call_name = "call_IO";
StatementMatcher CallIOMatcher = callExpr(callee(functionDecl(hasName(io_call_name)))).bind("CallIO"); 
class CallIOHandler : public MatchFinder::MatchCallback {

public:
  CallIOHandler() {}

 virtual void run(const MatchFinder::MatchResult &Result) {

  const CallExpr *call = Result.Nodes.getNodeAs<clang::CallExpr>("CallIO");
  
  ASTContext *Context = Result.Context;
  
  if (!call || !Context->getSourceManager().isWrittenInMainFile(call->getBeginLoc()))
      return ;

  int argc = call->getNumArgs();
  string argv[argc];
  
  extractCallArguments(call, argv);
  
  if(argv[0].find("Timely") != std::string::npos){
  if(argc == 4)
    replaceArgumentsInTimelyRetValTemplate(argv,io_call_timely_retval_template, argc);
  else  if(argc == 3)
    replaceArgumentsInTimelyTemplate(argv,io_call_timely_template, argc);
      
        transfd_code_writer.InsertText(call->getBeginLoc(), io_call_timely_retval_template, true, true);  	
  }
  else if (argv[0].find("Single") != std::string::npos){
    if(argc == 3){
	replaceArgumentsInSingleRetValTemplate(argv,io_call_single_retval_template, argc);
        transfd_code_writer.InsertText(call->getBeginLoc(), io_call_single_retval_template, true, true);
      }
    else if(argc == 2){
	replaceArgumentsInSingleTemplate(argv,io_call_single_template, argc);
        transfd_code_writer.InsertText(call->getBeginLoc(), io_call_single_template, true, true);
       }
  }
  else if (argv[0].find("Always") != std::string::npos){
    if(argc == 3){
       replaceAll(io_call_always_retval_template,"*retval*",argv[1]);
       replaceAll(io_call_always_retval_template,"*op_name*",argv[2]);
       transfd_code_writer.InsertText(call->getBeginLoc(), io_call_always_retval_template, true, true);
       }
   else if(argc == 2)
        transfd_code_writer.InsertText(call->getBeginLoc(), argv[1], true, true);
  }
 }
};

string io_block_end_temp="";
string io_block_begin_name = "IO_Block_begin";
StatementMatcher io_block_begin_Matcher =  callExpr(callee(functionDecl(hasName(io_block_begin_name)))).bind("IOBlockBegin");
class IOBlockBeginHandler : public MatchFinder::MatchCallback {
public:

  IOBlockBeginHandler() {}

  virtual void run(const MatchFinder::MatchResult &Result) {
  const CallExpr *call = Result.Nodes.getNodeAs<clang::CallExpr>("IOBlockBegin");
  ASTContext *Context = Result.Context;
  
  if (!call || !Context->getSourceManager().isWrittenInMainFile(call->getBeginLoc()))
      return ;
  
  int argc = call->getNumArgs();
  string argv[argc];
  
  extractCallArguments(call, argv);

  // Add additional code
  if(argv[0].find("Timely") != std::string::npos){
      replaceArgumentsInTimelyBlockTemplate(argv,io_block_begin_timely_retval_template, argc);
      transfd_code_writer.ReplaceText(call->getBeginLoc(), io_block_begin_timely_retval_template.length(), io_block_begin_timely_retval_template);//
  }
  else if (argv[0].find("Single") != std::string::npos){
  	string begin  = io_block_begin_single_template;
  	string end  = io_block_end_single_template;  	
  	replaceArgumentsInSingleBlockTemplate(argv,begin, end, argc);
  	io_block_end_temp = end;
        transfd_code_writer.InsertText(call->getBeginLoc(), begin, true, true);  	
  }  
}  
};

bool bloc_trt_g=0;
string io_block_end_name = "IO_Block_end";
StatementMatcher io_block_end_Matcher =  callExpr(callee(functionDecl(hasName(io_block_end_name)))).bind("IOBlockEnd");
class IOBlockEndHandler : public MatchFinder::MatchCallback {
public:

  IOBlockEndHandler() {}

  virtual void run(const MatchFinder::MatchResult &Result) {
  
  const CallExpr *call = Result.Nodes.getNodeAs<clang::CallExpr>("IOBlockEnd");
  ASTContext *Context = Result.Context;
  
  if (!call || !Context->getSourceManager().isWrittenInMainFile(call->getBeginLoc()))
      return ;
  
  int argc = call->getNumArgs();
  string argv[argc];
  
  extractCallArguments(call, argv);
  
  transfd_code_writer.InsertText(call->getBeginLoc(), io_block_end_temp, true, true);  	//io_call_timely_retval_template.replace(index, len_of_call,);
  }  
};


string CallerFunc = "";
class EaseIOASTVisitor : public clang::RecursiveASTVisitor<EaseIOASTVisitor> {
  clang::SourceManager &SourceManager;

public:
  EaseIOASTVisitor(clang::SourceManager &SourceManager)
     : SourceManager(SourceManager) {}

  virtual bool VisitFunctionDecl(FunctionDecl *func) {
  
     if (!func || !SourceManager.isWrittenInMainFile(func->getSourceRange().getBegin()))
      return true;
        string funcName = func->getNameInfo().getName().getAsString();
        CallerFunc = funcName;
        
        //for each function check if the function is in the list modifying global variables. if yes add DM privatization logic
       if (functionIsModifyingGV(functionList, sizeOfFuncList, funcName)) {

        // add privatization logic at the start of the function. 
        
        dma_priv = getDMAPrivCodeString(functionList, sizeOfFuncList, funcName); 
        DMA_func_start = func->getBody()->getBeginLoc().getLocWithOffset(3);
        transfd_code_writer.InsertText(func->getBody()->getBeginLoc().getLocWithOffset(3), dma_priv, true, true); 
        }         
        return true;     
    }     
     
    virtual bool VisitStmt(Stmt *st) {
      if (!st || !SourceManager.isWrittenInMainFile(st->getSourceRange().getBegin()))
      return true;

        if (auto *ret = dyn_cast<CallExpr>(st)) {
		string funcName  = ret->getDirectCallee()->getNameInfo().getName().getAsString();
        	if(funcName == "EASEIO_DMA_copy"){
        	   transfd_code_writer.InsertText(ret->getEndLoc().getLocWithOffset(3), DMA_var_priv_func_end_template, true, true); 
        	}
        }
        return true;
    }

private:
  string dma_priv;
  SourceLocation DMA_func_start;
  string getDMAPrivCodeString(GV_to_Func_Map *arr, int size, string fName){
  string res_if = "";
  string res_else = "";
  string res_priv = "";
  string final_res = DMA_var_priv_func_start_template;
  std::size_t found;
    for(int i=0;i<size;i++)
    {
       if(arr[i].funcName==fName)
        {      
    	   for(int j=0; j < arr[i].sizeOfVarList ;j++){
      	        res_if += DMA_var_priv_template_if;
      	        res_else += DMA_var_priv_template_else;
      	        res_priv = private_var_template;

    		replaceAll(res_if,"*var_name*",arr[i].variableList[j]);
		replaceAll(res_else,"*var_name*",arr[i].variableList[j]);
		replaceAll(res_priv,"*var_name*",arr[i].variableList[j]);
		replaceAll(res_priv,"*type*",arr[i].datatypes[j]);
		found = private_var_list.find(res_priv);
		if (found==std::string::npos)
		   private_var_list += res_priv;	
    	   }
    	   break;
    	}
     }
     if(res_if == "" || res_else == "")
       return "";
     replaceAll(final_res,"*if_template*",res_if);
     replaceAll(final_res,"*else_template*",res_else);
  
     return final_res;
     
  }
 
  bool functionIsModifyingGV(GV_to_Func_Map *arr, int size, string fName){
    for(int i=0;i<size;i++)
    {
       if(arr[i].funcName == fName && !arr[i].isVisited)
       {
          arr[i].isVisited = true;
          return true;
       }
     }
    return false;
  }
 
 std::string getDeclLocation(clang::SourceLocation Loc) const {
    std::ostringstream OSS;
    OSS << SourceManager.getFilename(Loc).str() << ":"
        << SourceManager.getSpellingLineNumber(Loc) << ":"
        << SourceManager.getSpellingColumnNumber(Loc);
    return OSS.str();
  }
};

// ASTConsumer for the Semantic Analyzer. Runs the matchers and traverses the 
// AST to inject RegionalPrivatization Logic.

class EaseIOASTConsumer : public ASTConsumer {

    EaseIOASTVisitor visitor;

public:

  // override the constructor in order to pass SM
  EaseIOASTConsumer(clang::SourceManager &SM) : visitor(SM){
    Matcher.addMatcher(CallIOMatcher, &IOHandler);
    Matcher.addMatcher(io_block_begin_Matcher, &BlockBeginHandler);
    Matcher.addMatcher(io_block_end_Matcher, &BlockEndHandler);
  }

  void HandleTranslationUnit(ASTContext &Context) override {
    // Run the matchers when we have the whole TU parsed.
    Matcher.matchAST(Context);
    auto Decls = Context.getTranslationUnitDecl()->decls();
     for (auto &Decl : Decls) {
          const auto& FileID = Context.getSourceManager().getFileID(Decl->getLocation());
          if (FileID != Context.getSourceManager().getMainFileID())
                continue;
            visitor.TraverseDecl(Decl);
     }

    auto comments = Context.getRawCommentList().getComments();
    for (auto comment : comments) {
      if (comment->getRawText(Context.getSourceManager()).str() == "/**global_variables*/"){
	      transfd_code_writer.ReplaceText(comment->getBeginLoc(), getAllGlobalVariables());
      }
    }
    
  }

private:
  CallIOHandler IOHandler;
  IOBlockBeginHandler BlockBeginHandler;
  IOBlockEndHandler BlockEndHandler;
  MatchFinder Matcher;
};


string output_file_name;
// For each source file provided to the tool, a new FrontendAction is created.
class EaseIOFrontendAction : public ASTFrontendAction {

public:
  EaseIOFrontendAction() {}
  void EndSourceFileAction() override {
//    transfd_code_writer.getEditBuffer(transfd_code_writer.getSourceMgr().getMainFileID()).write(llvm::outs());
    std::error_code error_code;
    llvm::raw_fd_ostream outFile(output_file_name, error_code, llvm::sys::fs::F_None);
    transfd_code_writer.getEditBuffer(transfd_code_writer.getSourceMgr().getMainFileID()).write(outFile);
    outFile.close();
    
  }

  std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI,
                                                 StringRef file) override {
    CI.getPreprocessor().SetSuppressIncludeNotFoundError(true);
    CI.getDiagnostics().setClient(new IgnoringDiagConsumer());
    transfd_code_writer.setSourceMgr(CI.getSourceManager(), CI.getLangOpts());
    return llvm::make_unique<EaseIOASTConsumer>(CI.getSourceManager());
  }

};

/******************************************************************* DMA regional privatization */
class GlobalVariableFinder final
    : public RecursiveASTVisitor<GlobalVariableFinder> { // for regional privatization logic
public:

  static bool find(FunctionDecl *CandidateFunction) {
    GlobalVariableFinder GVFinder;
    GVFinder.TraverseDecl(CandidateFunction);
    if(GVFinder.Found){
     /*Store the list of all global variables accessed in the function*/
      functionList[sizeOfFuncList].funcName = CandidateFunction->getNameInfo().getName().getAsString();
      functionList[sizeOfFuncList].isVisited = false;
      sizeOfFuncList++;    
    }   

    return GVFinder.Found;
  }

  bool VisitDeclRefExpr(DeclRefExpr *SymbolUse) {

    if (auto *Declaration = dyn_cast<VarDecl>(SymbolUse->getDecl())) {
      Found = Declaration->hasGlobalStorage();
      bool isAConstData = false;
      if(Declaration->getType().getAsString().find("_q15") != std::string::npos)
      		isAConstData = true;
      if (Found && !isAConstData) { 

      bool funDecl = isAFuncDecl(SymbolUse->getNameInfo().getAsString());
      bool VarFound = varIsInList(functionList[sizeOfFuncList].variableList,functionList[sizeOfFuncList].sizeOfVarList,SymbolUse->getNameInfo().getAsString());

      //check if variable is already in the list and is not a function decl
      if (!VarFound&& !funDecl) {
        functionList[sizeOfFuncList].variableList[functionList[sizeOfFuncList].sizeOfVarList] = SymbolUse->getNameInfo().getAsString();
        functionList[sizeOfFuncList].datatypes[functionList[sizeOfFuncList].sizeOfVarList] = Declaration->getType().getAsString();        
        functionList[sizeOfFuncList].sizeOfVarList++;
      }
    }
    }
    return true;
  }

private:
  bool isAFuncDecl(string vardecl){
  	if (vardecl.find("_task") != std::string::npos){
  	return true;
  	}
  return false;
  }
  bool varIsInList(string *arr, int size, string varName){
    for(int i=0;i<size;i++)
    {
       if(arr[i]==varName)
       {
       return true;
       }
     }
    return false;
  }
  
  void printList(string *arr, int size){
    for(int i=0;i<size;i++)
    {
    	errs()<< arr[i]<<"\n";
    }

  }
  
  bool Found = false;
};

class EaseIO_DMA_ASTConsumer : public ASTConsumer,
      public RecursiveASTVisitor<EaseIO_DMA_ASTConsumer> {
public:
  explicit EaseIO_DMA_ASTConsumer(ASTContext *Context): Context(Context) {}
  
  void HandleTranslationUnit(ASTContext &C) {
       this->TraverseTranslationUnitDecl(C.getTranslationUnitDecl());
  }

  bool VisitFunctionDecl(FunctionDecl *CandidateFunction) {
   if (!CandidateFunction || !Context->getSourceManager().isWrittenInMainFile(CandidateFunction->getLocation()))
    return true;
    
    GlobalVariableFinder::find(CandidateFunction);

    return true;
  }

private: 

  ASTContext *Context;
 
};
// For each source file provided to the tool, a new FrontendAction is created.
class EaseIO_DMA_FrontendAction : public ASTFrontendAction {
public:
  EaseIO_DMA_FrontendAction() {}

virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
    clang::CompilerInstance &Compiler, llvm::StringRef InFile) {
    Compiler.getPreprocessor().SetSuppressIncludeNotFoundError(true);
//    Compiler.getDiagnostics().setClient(new IgnoringDiagConsumer());
    return std::unique_ptr<clang::ASTConsumer>(
        new EaseIO_DMA_ASTConsumer(&Compiler.getASTContext()));
  }
  /*write the final output to the console*/
  void EndSourceFileAction() override {
     //printGVMap(functionList,sizeOfFuncList);
    //TheRewriter.getEditBuffer(TheRewriter.getSourceMgr().getMainFileID())    .write(llvm::outs());
  }
private:

 void printGVMap(GV_to_Func_Map *arr, int size){
    for(int i=0;i<size;i++)
    {
    	errs()<<" Function Name: "<< arr[i].funcName << " Vars:";

    	for(int j=0;j < arr[i].sizeOfVarList ;j++){
    		errs()<<arr[i].variableList[j]+", ";
    	}
    	errs()<<"\n";
    	
     }
  }
  
};

int main(int argc, const char **argv) {
    
    llvm::errs() << "argc "<<argc<<"\n";
    if (argc != 3) {
        llvm::errs() << "Usage: easeIO-c <input-filename along with path> <output-filename along with path> [-I header files]\n";
        return 1;
    }

  output_file_name = argv[2];


  CommonOptionsParser op(argc, argv, MatcherSampleCategory);
  ClangTool Tool(op.getCompilations(), op.getSourcePathList());
  Tool.run(newFrontendActionFactory<EaseIO_DMA_FrontendAction>().get());



  return Tool.run(newFrontendActionFactory<EaseIOFrontendAction>().get());
}
