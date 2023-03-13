
# EaseIO Overview
EaseIO is a novel programming model that introduces re-execution semantics of IO operations for intermittent computing. Re-executed IO operations in intermittent systems' tasks might lead to memory inconsistencies and high energy consumption. EaseIO offers new interfaces to call IO functions to overcome memory inconsistencies and save energy. Programmers can call IO functions with re-execution semantics annotations thanks to the EaseIO interfaces. 

This repository contains the code associated with the paper #19 "Efficient and Safe I/O Operations for Intermittent Systems".

DOI: https://doi.org/10.1145/3552326.3587435

AE Version: https://github.com/tinysystems/easeIO/commit/1136f0c6c051516f77291383a93d4e6e7ca03ce2


# Respository structure
<p>EaseIO consists of two main components EaseIO compiler front-end and EaseIO runtime.</p>
 
## Compiler-frontend
EaseIO compiler-frontend is responsible for performing semantic analysis to inject appropriate code in the original file.

### How to run it?
You can perform transformation using the following steps and commands.

1- Run the following command to install Clang
```shell script
sudo apt install clang lldb lld
``` 
2- Use the llvm-build.sh to download and compile the llvm-9.0.1.
```shell script
sudo llvm-build.sh 
``` 
3- Afterwards, put the compiler frontend code in the /llvm/tools/clang/tools/easeIO folder.

4- Add path of this subdirectory in the cmakelist file located one folder above this one i.e. /llvm/tools/clang/tools.

5- Run make using the following commands. For subsequent make commands, you can simply call make easeIO-c.
```shell script
cd /easeIO/llvm-9.0.1-build/build
sudo make 
```
6- Now run easeIO-c.sh script to run the transformation for all the codes.

<mark>Note:</mark> easeIO-c.sh contains path to the source file that the user wants to parse and location of the destination folder where the output will be written. 
You can change the path of the LLVM folder and benchmark folders as per location on your machine. However, please make sure you have sperate folders for <b>Originals</b> and <b>Transformed</b>. EaseIO is programmed to keep these two files separate for the ease of use. So the folder for transformed codes should on the same level and path (similar to how it is in the given code structure).

## Runtime
The transformed code is then linked with the EaseIO runtime before burning on the microcontroller.

### How to run it?
We provide the ready to run project for one of the benchmarks (FIR filter). Following are the steps to run the code. Please note that we use Code Composer Studio to run the project and tested our benchmarks on Ubuntu20.04 linux environment.  


  1. Select the [CCSProject](./CCSProject) folder as the workspace and launch
  2. Copy the transformed file from [EASEIO-compiler/test](https://github.com/tinysystems/easeIO/tree/main/EaseIO-compiler/test) to the Benchmarks folder in the project
  3. Just click the debug button. Now the project is ready to go.

### Requirements

Hardware Requirement:
- MSP430FR5969 board

Software Requirements
- LLVM9.0.1

<!---
## Getting Started

For ease-of-use, we have transformed the code for Single timely operation. 
-->
## Basic Application development with EaseIO
In EaseIO-compiler/test/Transformed/ directory, there are sample benchmark applications implemented using EaseIO. The Timely_Temp_Org_transformed.c file is one of our uni-task benchmark applications which shows an example of the <em> Timely</em> re-execution semantic of the EaseIO. The application gets hundred temperature sensor measurements. The time constraint of this application is finishing the task within 10 msec after the sensor is read. If the power failure time interval exceeds 10 ms, then EaseIO runtime gets the temperature value again. Otherwise, EaseIO runtime skips measuring temperature and finishes the remaining part of the task. 
```c
__nv  uint64_t exe_number = 0;

void task_temp()
{
    
    int temp;

    while(sample < 1000){
        P1OUT = 0x01;
        call_IO("Timely", 10000, temp, msp_sample_temperature());

        avg_temp = avg_temp*sample + temp;
        sample ++;
        avg_temp /= sample;
        TRANSITION_TO(task_init);
    }
    P1OUT = 0x02;
    while(1);
}

```
We keep track of the application execution via LEDs on P1.0 (red) and P1.1 (green). During the whole application, you will observe that red LED is turned on. When the application is completed, the red LED turns off and the green one turns on. 
To intermittently run the application,  <em> INTERMITTENT </em> macro should be defined. The LEDs run the same logic during the intermittent execution. 
## Copyright
MIT License. See the [license](https://github.com/tinysystems/easeIO/blob/main/LICENSE.txt)file for details.
 
<!---

### Acknowledgements {#custom-id}
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

