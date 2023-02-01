
# EaseIO Overview
This repository contains the code associated with the paper #19 "Efficient and Safe I/O Operations for Intermittent Systems".

EaseIO is a novel programming model that introduces re-execution semantics of IO operations for intermittent computing. Re-executed IO operations in intermittent systems' tasks might lead to memory inconsistencies and high energy consumption. EaseIO offers new interfaces to call IO functions to overcome memory inconsistencies and save energy. Programmers can call IO functions with re-execution semantics annotations thanks to the EaseIO interfaces. 
# Respository structure
<p>EaseIO consists of two main components EaseIO compiler front-end and EaseIO runtime.</p>
 
## Compiler-frontend
EaseIO compiler-frontend is responsible for performing semantic analysis to inject appropriate code in the original file. 

### How to run it?
You canperform transformation using the following steps.
<ol>
  <li>Use the llvm-build.sh to download and compile the llvm-9.0.1.</li>
  <li>Afterwards, put the compiler frontend code in the /llvm/tools/clang/tools/easeIO folder</li>
  <li>add path of this subdirectory in the cmakelist file located one folder above this one i.e. /llvm/tools/clang/tools .</li>
  <li>Now run easeIO.sh script to run the transformation for all the codes.</li>
</ol>

You can change the path of the LLVM folder and benchmark folders as per location on you machine. However, please make sure you have sperate folders for ==Originals== and ==Transformed==. EaseIO is programmed to keep these two files separate for the ease of use. So the folder for transformed codes should on the same level and path (similar to how it is in the given code structure).

#### Runtime
Compiler-frontend alone cannot do the job completely. EaseIO runtime is designed to complement the frontend.  

##### How to run it?
Import the code 
<ol>
  <li>Use the llvm-build.sh to download and compile the llvm-9.0.1.</li>
  <li>Afterwards, put the compiler frontend code in the /llvm/tools/clang/tools/easeIO folder</li>
  <li>add path of this subdirectory in the cmakelist file located one folder above this one i.e. /llvm/tools/clang/tools .</li>
  <li>Now run easeIO.sh script to run the transformation for all the codes.</li>
</ol>

### What can I reproduce

Single timely operation


### Acknowledgements {#custom-id}

### Copyright
MIT License. See the [license](https://github.com/tinysystems/easeIO/blob/main/LICENSE.txt)file for details.
 
<!---
Software dependencies
LLVM 9.0.1

Hardware Dependencies
MSP430FR5969 boards

### Setup

run the llvm-build.sh 

Software dependencies
LLVM 9.0.1

Hardware Dependencies
MSP430FR5969 boards
-->

