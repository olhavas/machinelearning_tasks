# Pisi
## Trainer
Your task is to prepare a program that represents a trainer of a linear function (polynomial of degree k=1)
approximating given training points in n dimensions. To gain its objective program should use gradient descent
method. The unsepcified parameters of the method should be selected by the author of the program. In particular
the author should decide when the proces of training should be stopped. This program will be executed in the
following way:


`program -t train_set.txt -i data_in.txt -o data_out.txt < description_in.txt > description_out.txt
`

where descripion_in.txt describes the initial polynomial and descripion_out.txt represent the polynomial after
given number of training iterations (format of this file was described in a previous task). Number of iterations
will be specified in file **data_in.txt**:

`iterations=number`
Since the training can be stopped earlier the actual number of performed iterations should written (in the same
format) in file data_out.txt. The train_set.txt file describes training points in successive lines. Every line contains
n+1 real numbers separated with spaces. First n numbers represent input variables and the last number represents
the expected output of the polynomial.
The submitted solution should contain both Trainer and Trainee.
It should be assumed that all text files contain an empty line at the end of the file and that the Unix encoding of
the end of line character is used. All the real values should use dot instead of comma as a decimal point
separator.
Sample input:
### description_in.txt
`1 1`\
`1 1.0`\
`0 1.0`
### data_in.txt
`iterations=1000`
### train_set.txt

`-2.963146353518017 -9.417057387429033`\
`-2.927883513943802 -9.251066001047633`\
`-2.7783065727793685 -8.475916690802611`\
`-2.683130711747852 -8.331287155983432`\
`-2.3206093041544853 -7.9965325413055774`\
`-1.889469789839917 -6.824516314481335`\
`-1.5878137358720397 -6.1352370850961115`\
`-0.984292345106387 -5.257092674577793`\
`-0.7843400030604699 -4.608445751228483`\
`-0.07426993267440718 -2.906071071142956`\
`0.103462158615236 -3.1784025020361613`\
`0.285716146164682 -2.344747700515421`\
`0.5120805208655259 -1.4854960301425886`\
`1.2061333089961908 -0.4357201817382792`\
`1.455224892197534 0.09662992217538935`\
`1.7728587630956296 0.3294016432827813`\
`2.0302086584052805 1.3447913315499318`\
`2.6920467885507557 1.9542213647102935`\
`2.927587177133674 2.669644050607312`\
`3.497560340314764 4.404791492050249`
### Expected output:
It depends on the choice of the gradient descent parameters. Since the sample input is in n=1 dimension the
linear function and training set can be plotted to check the correctnes of the implementation.
Program can be prepared using one of the approaches described below. The solution must be submitted as a
single zip file which directly (without any unnecessary directory) contains source code and proper farm
configuration file. Program will be compiled (if necessary) and executed in a directory where this zip file will be
decompressed. No external dependecies are allowed (only the standard library should be used).
## **Java RAW**
**description**\
Java code may be composed of many java files organized in an arbitrary package structure
(packages should be the only subdirectories of zip file). The farm file should specify the fully
qualified name (with packages) of the classes which contain main function.\
**farm file**\
type=java_raw\
 _fully qualified names of the classes representing trainee and trainer_\
trainee="package.Trainee"\
trainer="package.Trainer"\
**environment** java 1.8.0_66\
**compilation** javac -cp . *.java (for all the packages)\
**execution** java -cp . $trainer -t train_set.txt -i data_in.txt -o data_out.txt < description_in.txt >
description_out.txt
## **C++ RAW**
**description**\
C++ code can be composed of many source and header files. The only limitation is that all those
files should be located in a main directory of zip file. The farm file should specify the source files
required to build the programs (one of them should contain main function).\
**farm file**\
type=cpp_raw\
 _names of source files, separated with spaces, required to build trainee and trainer_\
trainee="trainee.cpp module.cpp"\
trainer="trainer.cpp module.cpp"\
**environment** g++ 4.8.1\
**compilation** g++ -std=c++0x -o trainer $trainer\
**execution** trainer -t train_set.txt -i data_in.txt -o data_out.txt < description_in.txt > description_out.txt
## **Python RAW**
**description** \
Python code should be composed of the scripts and modules organized in packages structure
(packages should be the only subdirectories of zip file). The farm file should specify which scripts
(in a main directory) should be executed as actual programs.\
 **farm file** \
type=python_raw\
 _name ot the python script file representing trainee_\
trainee="trainee.py"\
trainer="trainer.py"\
**environment** python 2.7.5+\
**compilation** none\
**execution** python $trainer -t train_set.txt -i data_in.txt -o data_out.txt < description_in.txt >
description_out.txt