#!/bin/bash



FILENAME="FIR_Filter_EASEIO_Org"

LLVMHOME=~/easeIO/llvm-9.0.1-build/ # take this as input
LLVMBUILD=~/easeIO/llvm-9.0.1-build/build/ # take this as input  
CODEBASE=/home/saad/easeIO/EaseIO-codebase # where original codes are located
ORGEBASE=/home/saad/easeIO/EaseIO-codebase/Benchmarks/Originals # where original codes are located
TARGET_FOLDER=/home/saad/easeIO/EaseIO-codebase/Benchmarks/Transformed # where transformed codes will go.
TARGET_FILENAME=transformed_$FILENAME # name of the file being transformed

INCLUDES="-I$LLVMHOME/llvm/tools/clang/include/ -I$LLVMHOME/llvm/include -I$LLVMHOME/build/tools/clang/include -I$LLVMHOME/build/include -I$CODEBASE -I$CODEBASE/libmsp -I$CODEBASE/dsplib/include -I$CODEBASE/dsplib/source/vector -I$CODEBASE/inputs/ -I$CODEBASE/libmsp/ -I$CODEBASE/libalpaca/" 

$LLVMBUILD/bin/easeIO-c $ORGEBASE/$FILENAME.c -- $INCLUDES -c



echo "Done"

