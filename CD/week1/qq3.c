#include<stdio.h>
#include<stdlib.h>
int main(){
    FILE *fptr1, *fptr2, *fptr3;
    char filename[100];
    char c1, c2;
    printf("Enter name of 1st source file:");
    scanf("%s",filename);
    fptr1=fopen(filename,"r");
    if(fptr1!=NULL){
        printf("Cannot open file");
        exit(0);
    }
    printf("Enter name of 2nd source file:");
    scanf("%s",filename);
    fptr2=fopen(filename,"r");
    if(fptr2!=NULL){
        printf("Cannot open file");
        exit(0);
    }
    printf("Enter name of destination file:");
    scanf("%s",filename);
    fptr3=fopen(filename,"w");
    c1=fgetc(fptr1);
    c2=fgetc(fptr2);
    while(c1!=EOF || c2!=EOF){
        if(c1!=EOF){
            while(c1!=EOF && c2!='\n'){
               fputc(c1,fptr3);
               c1=fgetc(fptr1); 
            }
            fputc('\n',fptr3);
        }
        if(c2!=EOF){
            while(c2!='\n'||c2!=EOF){
                fputc(c2,fptr3);
                c2=fgetc(fptr2);
            }
            fputc('\n',fptr3);
        }
        c1=fgetc(fptr1);
        c2=fgetc(fptr2);
    }
    printf("Contents copied to %s",filename);
    fclose(fptr1);
    fclose(fptr2);
    fclose(fptr3);
    return 0;

}