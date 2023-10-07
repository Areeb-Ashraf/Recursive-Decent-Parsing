%{
#include <stdio.h>
%}

%option noyywrap

%%

[0-9]           { fprintf(yyout, "%s,integer\n", yytext); }
[+\-*/()]       { fprintf(yyout, "%s,operator\n", yytext); }
[ \t]           { /* Ignore whitespace */ }
.               { fprintf(stderr, "Invalid character: %s\n", yytext); }

%%

int main() {
    char expression[100];  // Assuming a maximum expression length of 100 characters
    FILE *outputFile = fopen("lex_output.txt", "w");
    
    if (outputFile == NULL) {
        fprintf(stderr, "Error opening output file\n");
        return 1;
    }
    
    // Redirect output to the lex_output.txt file
    yyout = outputFile;
    
    printf("Enter an expression: ");
    scanf("%99[^\n]", expression);  // Read input from the user
    
    // Initialize the Flex lexer with the user's input
    yy_scan_string(expression);
    
    int token;
    while ((token = yylex()) != 0) {
        // Only write the desired output to the file
        if (token == 1 || token == 2) { // 1 represents INTEGER, 2 represents OPERATOR
            fprintf(yyout, "%s\n", yytext);
        }
    }
    
    fclose(outputFile);
    
    return 0;
}