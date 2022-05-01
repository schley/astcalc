# numberCalc

AST: https://web.cs.wpi.edu/~kal/PLT/PLT6.3.6.html


regex and handmade parser create a number only calculator

Required:  

           1. clang++ that handles compiler option std=c++20  
              (also tested with std=c++14)
           2. Makefile (on ubuntu ==> linux> sudo apt install build-essentials )

Experiment with C++14 regex to create a lexer.  

Code a term-factor-expression parser to actually calculate values ...

example:

linux> make

linux> ./t6calc    # test number 6 for the calc.  Change exe name in Makefile as desired

numberCalc:  bunch of debug statements.  Will prompt to get equation ... limited error processing.
             The number on left indicates how many requests performed.

1> 45 * (3 / 15)

numberCalc: more debug

numberCalc: 45 * (3 / 15) = 2.8

2> exit


No state other than line counter for prompt is maintained between lines.  
