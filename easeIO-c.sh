
FILENAME="FIR_Filter_EASEIO_Org"
#FILENAME="Single_DMA_Org"
#FILENAME="Timely_Temp_Org"
#FILENAME="Weather_App_EASEIO_Org"

<<<<<<< HEAD
LLVMHOME=~/easeIO/llvm-9.0.1-build/ # take this as input
LLVMBUILD=~/easeIO/llvm-9.0.1-build/build/ # take this as input  
CODEBASE=/home/saad/easeIO/EaseIO-codebase # where original codes are located
ORGEBASE=/home/saad/easeIO/EaseIO-codebase/Benchmarks/Originals # where original codes are located
TARGET_FOLDER=/home/saad/easeIO/EaseIO-codebase/Benchmarks/Transformed # where transformed codes will go.
TARGET_FILENAME=transformed_$FILENAME # name of the file being transformed
=======


LLVMHOME=~/llvm # take this as input
LLVMBUILD=~/llvm/build # take this as input  
CODEBASE=~/easeIO/EaseIO-codebase # where original codes are located
ORGEBASE=~/easeIO/EaseIO-compiler/test/Originals # where original codes are located
TARGET_FOLDER=~/easeIO/EaseIO-compiler/test/Transformed # where transformed codes will go.
COMPILER_FLAGS= -Wno-implicit-function-declaration  -Wno-int-conversion -Wno-int-to-pointer-cast -Wno-return-type -Wno-incompatible
>>>>>>> f628a1a2d64192cf4928d5c8c576d6e314312899

INCLUDES="-I$LLVMHOME/llvm/tools/clang/include/ -I$LLVMHOME/llvm/include -I$LLVMHOME/build/tools/clang/include -I$LLVMHOME/build/include -I$CODEBASE -I$CODEBASE/libmsp -I$CODEBASE/dsplib/include -I$CODEBASE/dsplib/source/vector -I$CODEBASE/inputs/ -I$CODEBASE/libmsp/ -I$CODEBASE/libalpaca/" 

$LLVMBUILD/bin/easeIO-c $ORGEBASE/$FILENAME.c -- $INCLUDES  -c $COMPILER_FLAGS




echo "Transformation Complete"
