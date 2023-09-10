#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define filein "q2source.c"
#define fileout "q2dest.c"
const char *direct[]={"#include","#define","#if"};

int is_directive(const char *str){
    for(int i=0; i<sizeof(direct)/sizeof(char *);i++){
        int len=strlen(direct[i]);
        if(strncmp(str,direct[i],len)==0){
            return 1;
        }
    }
    return 0;
}

int main(){
    char buf[2048];
    FILE *f1, *f2;
    f1=fopen(filein,"r");
    f2=fopen(fileout,"w");
    if(f1==NULL || f2==NULL){
        printf("Not Exist \n");
        return 1;
    }
    while(fgets(buf,2048,f1)!=NULL){
        if(!is_directive(buf)){
            fputs(buf,f2);
        }
    }
    fclose(f1);
    fclose(f2);
    f1=fopen(filein,"w");
    f2=fopen(fileout,"r");
    char copy;
    copy=getc(f2);
    while(copy!=EOF){
        putc(copy,f1);
        copy=getc(f2);

    }
    fclose(f1);
    fclose(f2);
}