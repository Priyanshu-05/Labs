#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE *fptr;
	char filename[100],c;
	int charCount=0;
	int lineCount=1;

	printf("Enter filename to open for reading: \n");
	scanf(" %s",filename);

	fptr = fopen(filename, "r");
	if(fptr==NULL)
	{
		printf("Cannot open file %s", filename);
		exit(0);
	}

	//Counting \n as one character and EOF as one character
    c = fgetc(fptr);

    if(c==EOF)
    {
    	printf("The number of characters and lines are: 0,0");
    	exit(0);
    }

	while(c!=EOF)
	{
		charCount++;
		if(c=='\n')
		{
			lineCount++;
		}
		c = fgetc(fptr);
	}

	charCount++;
	fclose(fptr);
	printf("The number of characters and lines are: %d, %d", charCount-lineCount, lineCount);
}