#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int id1;
struct Token {
    char lexeme[100];
    char type[100];
} token[100];

void setTokenArgs(char lexeme[], char type[]) {
    strcpy(token[id1].lexeme, lexeme);
    strcpy(token[id1].type, type);
    id1++;
}

int main() {
    int ch1;
    FILE *f1 = fopen("input.txt", "r"); // Corrected "open" to "fopen"
    if (f1 == NULL) {
        printf("File not found\n");
        return 1;
    }

    do {
        ch1 = getc(f1);
        char buf[100];
        int buflen = 0;

        while (isalpha(ch1)) {
            buf[buflen++] = ch1;
            ch1 = getc(f1);
        }
        buf[buflen] = '\0'; // Null-terminate the buffer

        if (strcmp(buf, "public") == 0 || strcmp(buf, "private") == 0 || strcmp(buf, "abstract") == 0 || strcmp(buf, "extends") == 0 || strcmp(buf, "static") == 0 || strcmp(buf, "interface") == 0) {
            char type[] = "keyword";
            setTokenArgs(buf, type);
        } else if (strcmp(buf, "int") == 0 || strcmp(buf, "float") == 0 || strcmp(buf, "boolean") == 0) {
            char type[] = "Datatype";
            setTokenArgs(buf, type);
        } else {
            int flag = 1;
            for (int i = 0; i < buflen; i++) {
                if (!isalpha(buf[i])) {
                    flag = 0;
                    break;
                }
            }
            if (flag == 1) {
                char type[] = "ID";
                setTokenArgs(buf, type);
            } else {
                char type[] = "Number";
                setTokenArgs(buf, type);
            }
        }
       
        if (ch1 == '{' || ch1 == '}' || ch1 == '[' || ch1 == ']') {
                char type[] = "Brackets";
                buf[0] = ch1;
                buf[1] = '\0';
                setTokenArgs(buf, type);
        }
        
    } while (ch1 != EOF);

    fclose(f1);

    // Print the tokens (you may need to adjust this part based on your needs)
    for (int i = 0; i < id1; i++) {
        printf("Lexeme: %s, Type: %s\n", token[i].lexeme, token[i].type);
    }

    return 0;
}
