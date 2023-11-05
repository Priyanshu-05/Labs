#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<ctype.h>

enum TokenType{
        STRING_LITERAL,
        OPERATOR,
        IDENTIFIER,
        KEYWORD,
        NUMBER,
        EOF_TOKEN
};

struct Token {
    char *lexeme;
    enum TokenType type;
    int row;
    int col;
};

struct Token tokenArray[100];
int tokenArrayIndex = 0;


enum TokenType iskeywordOrIdentifier(const char *str) {
    const char *keywords[] = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "while","public","interface","extends"
    };
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return KEYWORD;
        }
    }
    return IDENTIFIER;
}

int row = 0;
int col = 0;
struct Token getNextToken(FILE *srcFile){
    char buf[1000] = "\0";
    char c;
    int index = 0;
    printf("%d %s %d\n",ftell(srcFile),buf);
    struct Token tkn = {NULL,EOF_TOKEN,row,col++};
    while((c = fgetc(srcFile))!=EOF){
        if(isspace(c)){
            do{
                col++;
                c = fgetc(srcFile);
            }while(isspace(c));
        }
        if(c == '\n') {
            row++;
            col = 0;
            continue;
        }
        //check for string
        if(c == '\'' || c  == '"'){
            char startString = c;
            buf[index++] = c;
            col++;
            while((c = fgetc(srcFile))!=EOF && c != startString){
                buf[index++] = c;
                col++;
            }
            buf[index++] = c;
            col++;
            tkn.type = STRING_LITERAL;
        } //check for keyword //check for identifier
        else if(isalpha(c)||c == '_'){
            buf[index++] = c;
            col++;
            while((c = fgetc(srcFile))!=EOF && (isalnum(c) || c == '_') && !isspace(c)){
                buf[index++] = c;
                col++;
            }
            ungetc(c,srcFile);
            col--;
            tkn.type = iskeywordOrIdentifier(buf);
        }else if(isdigit(c)){
            buf[index++] = c;
            col++;
            while((c = fgetc(srcFile))!=EOF && isdigit(c)){
                buf[index++] = c;
                col++;
            }
            ungetc(c,srcFile);
            tkn.type = NUMBER;
        }else if(ispunct(c)){
            buf[index++] = c;
            col++;
            if(c == '+' || c== '-' || c=='/' || c == '*' || c == '='){
                char nextChar = fgetc(srcFile);
                if (nextChar == '=') {
                    buf[index++] = nextChar;
                    col++;
                } else {
                    ungetc(nextChar, srcFile);
                    col--;
                }
            }
            tkn.type = OPERATOR;
        }
        buf[index] = '\0';
        tkn.lexeme = strdup(buf);
        tokenArray[tokenArrayIndex++] = tkn;
        return tkn;
    }
}