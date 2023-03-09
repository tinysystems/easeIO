#add_subdirectory(EaseIO)

set(LLVM_LINK_COMPONENTS support)

add_clang_executable(easeIO-c
  EaseIO.cpp
  )
target_link_libraries(easeIO-c
  PRIVATE
  clangAST
  clangASTMatchers
  clangBasic
  clangFrontend
  clangSerialization
  clangTooling
  )
