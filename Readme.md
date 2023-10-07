# Expression Parser with Flex and C++

## Overview
This is a simple expression parser program implemented in C++ using Flex (Lexical Analyzer Generator). The program takes a mathematical expression as input, tokenizes it, and then constructs an Abstract Syntax Tree (AST) to represent the expression's structure. Finally, it prints the AST to the console.

## Files
`parser.cpp`: The C++ program that parses the input expression and constructs the AST.
`lex.l`: The Flex lexer specification file that tokenizes the input expression.
`run_program.sh`: A Bash shell script that compiles and runs the entire program.

## Features
- Parses basic mathematical expressions containing operators (+, -, *, /) and integers. 
- Handles whitespace and invalid characters gracefully.
- Builds an Abstract Syntax Tree (AST) to represent the expression's structure.
- Outputs the AST to the console.

## Prerequisites to run the program
- GCC (GNU Compiler Collection) for compiling C++ code.
- Flex (Lexical Analyzer Generator) for generating the lexer.
- Bash shell for running the provided shell script.

## Executing the program
To run the program you must first change the permisions of the `run_program.sh`. You can add the execute permission by running:
`chmod +x run_program.sh`

Then you can run the program by saying:
`./run_program.sh`

**Note:** This program works best on a linux terminal