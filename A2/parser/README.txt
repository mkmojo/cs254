Team Member:
Qiyuan Qiu, qqiu2, qqiu@cs.rochester.edu, 454
Spyridoula Gravani, sgravani, sgravani@cs.rochester.edu, 454

Files:
parse.cpp
parse.h
scan.cpp
scan.h
Makefile
README.txt
test.txt // a legal program, syntax error free
test6.txt // a illegal program with one syntax error

Progress
1. Finished
2. Finished
3. Finished 
4. Not finished
5. Immediate-error-recover works for our tests cases provided.

How to use:
    To compile:
        make clean && make
    To run with test program TestPgm.txt:
        cat TestPgm.txt | ./parse

Outline:
    For homework question 3:
        We installed exception handlers to production: stmt (), expr (), cond (), and factor_tail ().
        We mannually identified context specific follow sets (CSF) for each switch arm of some 
        production. 
        Only epsilon productions will directly take the CSF from its parent. Others will use the 
        precalculated CSF. 
        We followed the error handle algorithm from C-5 of companion site, with modification to the
        FOLLOW set in it. 
    For homework question 4:
        We ran out of time to have a fully correct version. 
