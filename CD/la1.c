#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Token types
typedef enum {
    OPERATOR,
    SPECIAL_SYMBOL,
    DIGIT,
    KEYWORD,
    IDENTIFIER,
    NEWLINE,
    INVALID
} TokenType;

FILE *input, *output;
int line = 1;

// Function to get the next token
TokenType getNextToken() {
    char ch = fgetc(input);

    if (ch == EOF) {
        return INVALID;
    }

    if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
        return OPERATOR;
    } else if (ch == ';' || ch == '{' || ch == '}' || ch == '(' || ch == ')' || ch == '?' ||
               ch == '@' || ch == '!' || ch == '%') {
        return SPECIAL_SYMBOL;
    } else if (isdigit(ch)) {
        return DIGIT;
    } else if (isalpha(ch)) {
        char str[20];
        int i = 0;
        str[i] = ch;
        i++;
        ch = fgetc(input);
        while (isalnum(ch) && ch != ' ') {
            str[i] = ch;
            i++;
            ch = fgetc(input);
        }
        str[i] = '\0';

        char *keyword[6] = {"int", "main", "if", "else", "do", "while"};
        for (int j = 0; j < 6; j++) {
            if (strcmp(str, keyword[j]) == 0) {
                return KEYWORD;
            }
        }

        return IDENTIFIER;
    } else if (ch == '\n') {
        line++;
        return NEWLINE;
    } else {
        return INVALID;
    }
}

int main() {
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    fprintf(output, "Token Type \t Lexeme\n\n");

    TokenType token;

    while ((token = getNextToken()) != INVALID) {
        char lexeme = fgetc(input);
        char *tokenTypeNames[] = {
            "OPERATOR", "SPECIAL_SYMBOL", "DIGIT", "KEYWORD", "IDENTIFIER", "NEWLINE", "INVALID"
        };
        fprintf(output, "%s\t\t %c\n", tokenTypeNames[token], lexeme);
    }

    fclose(input);
    fclose(output);

    return 0;
}
