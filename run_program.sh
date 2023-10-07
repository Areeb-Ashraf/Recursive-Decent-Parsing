#!/bin/bash

# Execute the commands one by one
flex lex.l
gcc lex.yy.c -o lex
./lex
g++ parser.cpp -o parser
./parser
