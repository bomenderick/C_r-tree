# R-Dimensional tree implemented in C and C++


NOTE: to interact with the algorithm, a g++ compiler is needed or any c++ compiler so as to produce appropriate executable files depending
    on the operating system of the working platform. executables in this package are generated using a LINUX UBUNTU 18.04 PLATFORM BASE,
    so can run only linux platform, reason to have an appropriate compiler to produce appropriate executables if working on a platform
    different from the above mentioned.

### For LINUX platform, the file "TestTimeAndSpaceOnTerminal.cpp" can easily be use for multiple input size and together determine the time
    and space used by each input size through algorithms various operations.

    #Assuming in the package directory (the directory of the open package with available files)
    to compile....
    #g++ R-Tree.h R-tree.cpp TestTimeAndSpaceOnTerminal.cpp -o "name of executable file that will be produce e.g. test"
    to run.....
    #for i in {10..50..10}; do ./test $i; done
     for an input size ranging from 10 to 50 with a step of 10(which can be modify as needed)

### For WINDOWS platform, the file "test1.cpp" can be use for random generation of inputs points with an input size specified in the test1.cpp
    through the constant "INPUT_SIZE".
    however if need of manual input arise, the file "main.cpp" can be use for a step by step interaction with the algorithm


#### See the "input file.txt" for a sample input and "output file.txt" for the corresponding output..


