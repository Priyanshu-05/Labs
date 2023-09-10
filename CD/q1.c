#include <stdio.h>
#include <stdlib.h>
int main()
{
    FILE *fptr;
    char filename[100], c;
    int charcount = 0, linecount = 0;
    printf("enter filename to open:\n");
    scanf("%s", filename);
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("Cannot open file\n");
        exit(0);
    }
    c = fgetc(fptr);
    while (c != EOF)
    {
        if (c == '\n')
        {
            linecount++;
        }
        else
        {
            charcount++;
        }
        c = getc(fptr);
    }
    printf("Total number of lines %d", linecount);
    printf("\nTotal number of characters %d", charcount);
    return 0;
}