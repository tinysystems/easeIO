#!/bin/bash



FILENAME="FIR_Filter_EASEIO_Org"

LLVMHOME=/home/saad/llvm # take this as input
LLVMBUILD=/home/saad/llvm/build # take this as input  
CODEBASE=/home/saad/easeIO/EaseIO-codebase/Benchmarks/Original # where original codes are located
TARGET_FOLDER=/home/saad/easeIO/EaseIO-codebase/Benchmarks/Transformed # where transformed codes will go.
TARGET_FILENAME=transformed_$FILENAME # name of the file being transformed

INCLUDES="-I$LLVMHOME/llvm/tools/clang/include/ -I$LLVMHOMEHOME/llvm/include -I$LLVMHOME/build/tools/clang/include -I$HOME/build/include -I$HOME/test -I$HOME/test/libmsp -I$HOME/dsplib/include -I$CODEBASE/dsplib/source/vector -I$CODEBASE/inputs/ -I$CODEBASE/libmsp/ -I/$CODEBASE/libalpaca/" 

$LLVMBUILD/bin/easeIO-c "$CODEBASE/Originals/($FILENAME).c -- $INCLUDES -c"



echo "Done"

