#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "getNextToken.h"
int findTable(struct sttable *tab, char *nam, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(tab[i].lexeme, nam) == 0)
            return 1;
    }
    return 0;
}
struct sttable fillTable(int sno, char *lexn, char *dt, char *t, int s, int a)
{
    struct sttable tab;
    tab.sno = sno;
    strcpy(tab.lexeme, lexn);
    strcpy(tab.dtype, dt);
    strcpy(tab.type, t);
    tab.size = s;
    tab.args=a;
    return tab;
}
int main()
{
    FILE *fa, *fb, *ftokens,*fsymboltable;
    int ca, cb;
    fa = fopen("digit.c", "r");
    if (fa == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    fb = fopen("digit1.c", "w+");
    fsymboltable = fopen("symboltable.txt", "w+");
    ftokens = fopen("tokens.txt", "w+");
    ca = getc(fa);
    while (ca != EOF)
    {
        if (ca == ' ')
        {
            putc(ca, fb);
            while (ca == ' ')
                ca = getc(fa);
        }
        if (ca == '/')
        {
            cb = getc(fa);
            if (cb == '/')
            {
                while (ca != '\n')
                    ca = getc(fa);
            }
            else if (cb == '*')
            {
                do
                {
                    while (ca != '*')
                        ca = getc(fa);
                    ca = getc(fa);
                } while (ca != '/');
            }
            else
            {
                putc(ca, fb);
                putc(cb, fb);
            }
        }
        else
            putc(ca, fb);
        ca = getc(fa);
    }
    fclose(fa);
    fclose(fb);
    fa = fopen("digit1.c", "r");
    if (fa == NULL)
    {
        printf("Cannot open file");
        return 0;
    }
    fb = fopen("temp.c", "w+");
    ca = getc(fa);
    while (ca != EOF)
    {
        if (ca == '"')
        {
            fputc(ca, fb);
            ca = getc(fa);
            while (ca != '"')
            {
                fputc(ca, fb);
                ca = fgetc(fa);
            }
        }
        if (ca == '#')
        {
            while (ca != '\n')
                ca = fgetc(fa);
        }
        else
            fputc(ca, fb);
        ca = fgetc(fa);
    }
    fclose(fa);
    fclose(fb);
    fa = fopen("temp.c", "r");
    fb = fopen("digit1.c", "w");
    ca = getc(fa);
    while (ca != EOF)
    {
        putc(ca, fb);
        ca = getc(fa);
    }
    fclose(fa);
    fclose(fb);
    remove("temp.c");
    FILE *f1 = fopen("digit1.c", "r");
    if (f1 == NULL)
    {
        printf("Error! File cannot be opened!\n");
        return 0;
    }
    struct token tkn;
    struct sttable st[10][100];
    int flag = 0, i = 0, j = 0;
    int tabsz[10];
    char w[25];
    w[0] = '\0';
    while ((tkn = getNextToken(f1)).row != -1)
    {
        fprintf(ftokens, "<%s, %d, %d, %s>\n", tkn.lexeme, tkn.row, tkn.col, tkn.type);
        if (strcmp(tkn.type, "Keyword") == 0)
        {
            if (isdtype(tkn.lexeme) == 1)
                strcpy(dbuf, tkn.lexeme);
        }
        else if (strcmp(tkn.type, "Identifier") == 0)
        {
            int count=0;
            strcpy(w, tkn.lexeme);
            tkn = getNextToken(f1);
            fprintf(ftokens, "<%s, %d, %d, %s>\n", tkn.lexeme, tkn.row, tkn.col, tkn.type);
            if ((strcmp(tkn.type, "LB")) == 0)
            {
                int position=0;
                char c = fgetc(f1);
                if(c==')')
                    count=0;
                else
                {
                    count=1;
                    while(c!=')')
                    {
                        position++;
                        if(c==',')
                            count++;
                        c = fgetc(f1);
                    }
                }
                if (findTable(st[i], w, j) == 0)
                {
                    ind++;
                    st[i][j++] = fillTable(ind, w, dbuf, "func", -1, count);
                }
            }
            if ((strcmp(tkn.type, "LS")) == 0)
            {
                if (findTable(st[i], w, j) == 0)
                {
                    tkn = getNextToken(f1);
                    fprintf(ftokens, "<%s, %d, %d, %s>\n", tkn.lexeme, tkn.row, tkn.col, tkn.type);
                    int s = 0;
                    if (strcmp(tkn.type, "Number") == 0)
                        s = atoi(tkn.lexeme);
                    ind++;
                    st[i][j++] = fillTable(ind, w, dbuf, "id", sz(dbuf) * s,0);
                }
            }
            else
            {
                if (findTable(st[i], w, j) == 0)
                {
                    ind++;
                    st[i][j++] = fillTable(ind, w, dbuf, "id", sz(dbuf),0);
                }
            }
        }
        else if (strcmp(tkn.type, "LC") == 0)
            flag++;
        else if (strcmp(tkn.type, "RC") == 0)
        {
            flag--;
            if (flag == 0)
            {
                tabsz[i] = j;
                i++;
                j = 0;
                ind = 0;
            }
        }
    }
    for (int k = 0; k < i; k++)
    {
        printTable(st[k], tabsz[k], fsymboltable);
        fprintf(fsymboltable, "\n==x==x==x===x==\n");
    }
    printf("Please check digit1.c, tokens.txt, symboltable.txt!\n");
    fclose(f1);
}
