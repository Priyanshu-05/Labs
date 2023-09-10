#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE *fptr1, *fptr2;
	char filename[100],c;

	printf("Enter name of source file: \n");
	scanf(" %s", filename);

	fptr1 = fopen(filename, "r");

	if(fptr1==NULL)
	{
		printf("Cannot open file %s", filename);
		exit(0);
	}

	printf("Enter name of destination file: \n");
	scanf(" %s", filename);

	fptr2 = fopen(filename, "w");

	fseek(fptr1, -1, SEEK_END);
	int length = ftell(fptr1);
	int i=1;

	c = fgetc(fptr1);
	while(length-i>=-1)
	{
		fputc(c,fptr2);
		i++;
		fseek(fptr1,-i, SEEK_END);
		c = fgetc(fptr1);
	}

	fclose(fptr1);
	fclose(fptr2);
	printf("The contents have been copied in reverse to %s", filename);

	return 0;
}