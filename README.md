Compiled and ran on Ubuntu 20.04 with g++ 9.3.0.
One of the particularly tricky aspects of this assignment
was to achieve cross-platform functionality of console
printing and clearing.

21:54:56 \***\* Incremental Build of configuration Debug for project Traffic-Simulator \*\***
make all
Building file: ../Road.cpp
Invoking: GCC C++ Compiler
g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"Road.d" -MT"Road.o" -o "Road.o" "../Road.cpp"
Finished building: ../Road.cpp

Building file: ../main.cpp
Invoking: GCC C++ Compiler
g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"main.d" -MT"main.o" -o "main.o" "../main.cpp"
Finished building: ../main.cpp

Building target: Traffic-Simulator
Invoking: GCC C++ Linker
g++ -o "Traffic-Simulator" ./Road.o ./main.o
Finished building target: Traffic-Simulator

21:54:57 Build Finished. 0 errors, 0 warnings. (took 661ms)
