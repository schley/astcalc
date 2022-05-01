# astcalc

based on pseudo-code posted on educational site
AST: https://web.cs.wpi.edu/~kal/PLT/PLT6.3.6.html

regex and handmade parser create a number only calculator

Required:  

           1. clang++ or g++ that handles compiler option std=c++20  
              (also tested with std=c++14)
           2. Makefile (on ubuntu ==> linux> sudo apt install build-essentials )
           3.  wsl> ninja --version  # answer: (1.10.2)
           4.  wsl> cmake --version  # answer: (3.22.3)

linux> git clone https://github.com/schley/astcalc
linux> cd astcalc
linux> mkdir build
linux> cd build
linux> cmake -G Ninja init ..
linux> ninja
linux> ./astcalc  (exit at prompt to terminate executable)

Experiment with C++14 regex to create a lexer.  

Code a term-factor-expression parser to actually calculate values ...

example:

linux> make

linux> ./astcalc    # test number 6 for the calc.  Change exe name in Makefile as desired

1> 45 * (3 / 15)

astcalc: 45 * (3 / 15) = 2.8

2> exit

No state other than line counter for prompt is maintained between lines.  
