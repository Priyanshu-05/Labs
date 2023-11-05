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
int tokenNumber = 0;

// Function to get the next token
TokenType getNextToken() {
    int i = 0;
    int flag = 0;
    char ch;
    char str[20];

    i = 0;
    flag = 0;
    ch = fgetc(input);

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
        str[i] = ch;
        i++;
        ch = fgetc(input);
        while (isalnum(ch) && ch != ' ') {
            str[i] = ch;
            i++;
            ch = fgetc(input);
        }
        str[i] = '\0';
        for (int j = 0; j <= 30; j++) {
            char keyword[30][30] = {"int", "main", "if", "else", "do", "while"};
            if (strcmp(str, keyword[j]) == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            return KEYWORD;
        } else {
            return IDENTIFIER;
        }
    } else if (ch == '\n') {
        line++;
        return NEWLINE;
    } else {
        return INVALID;
    }
}

// Function to print tokens
void printToken(TokenType token, char lexeme) {
    char *tokenTypeNames[] = {
        "OPERATOR", "SPECIAL_SYMBOL", "DIGIT", "KEYWORD", "IDENTIFIER", "NEWLINE", "INVALID"
    };
    fprintf(output, "%7d\t\t %7d\t\t %s\t %7c\n", line, tokenNumber, tokenTypeNames[token], lexeme);
    tokenNumber++;
}

int main() {
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    fprintf(output, "Line no. \t Token no. \t Token \t Lexeme\n\n");

    TokenType token;

    while ((token = getNextToken()) != INVALID) {
        printToken(token, fgetc(input));
    }

    fclose(input);
    fclose(output);

    return 0;
}
