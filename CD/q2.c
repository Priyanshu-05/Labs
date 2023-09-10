#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
int main()
{
    FILE *f1, *f2;
    char c, filename[100], temp[1024];
    int i = 0;
    printf("Enter the filename to open for reading: \n");
    scanf("%s", filename);
    f1 = fopen(filename, "r");
    printf("Enter the filename to open for writing: \n");
    scanf("%s", filename);
    f2 = fopen(filename, "w+");
    if (!f1 || !f2)
    {
        printf("Cannot open the file\n");
        exit(1);
    }
    while (c != EOF)
    {
        c = getc(f1);
        temp[i++] = c;
    }
    for (int j = (i - 2); j >= 0; j--)
    {
        c = temp[j];
        fputc(c, f2);
    }
    fseek(f1, 0, SEEK_END);
    int size = ftell(f1);
    printf("File size: %d\n", size);
}