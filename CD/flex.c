//1. Count the number of vowels and consonants in the given input.
%{
	int vC=0;
	int cC=0;
%}

%%
[aeiouAEIOU] {vC++;}
[b-df-hj-np-tv-zB-DF-HJ-NP-TV-Z] {cC++;}
%%

int yywrap()
{
	return 1;
}

int main()
{
	yyin=fopen("input.txt","r");
	yylex();
	printf("Number of vowels are: %d\n", vC);
	printf("Number of consonants are: %d\n", cC);
	fclose(yyin);
	return 0;
} 

//2. Count the number of words, characters, blanks and lines in a given text.
%{
	int wC=0;
	int cC=0;
    int lC=0;
    int bC=0;
%}

%%
[a-zA-Z]+ {wC++; cC += yyleng;}
\n {lC++;cC++;}
\t {bC++;cC++;}
" " {bC++;cC++;}
. {cC++;}
%%

int yywrap()
{
	return 1;
}

int main()
{
	yyin=fopen("input.txt","r");
	yylex();
	printf("Character : %d\nWords : %d\nBlanks : %d\nLines : %d\n",cC,wC,bC,lC);
	fclose(yyin);
	return 0;
} 

//3. Find the number of positive integer, negative integer, positive floating positive number and negative 
//floating point number
%{
	int pI=0;
	int nI=0;
    int pF=0;
    int nF=0;
%}

%%
[+]?[0-9]+ {pI++;}
[-][0-9]+ {nI++;}
[+]?[0-9]*"."[0-9]+ {pF++;}
[-][0-9]*"."[0-9]+ {nF++;}
%%

int yywrap()
{
	return 1;
}

int main()
{
	yyin=fopen("input.txt","r");
	yylex();
	printf("+ve Int : %d\n-ve Int : %d\n+ve Float : %d\n-ve Float : %d\n",pI,nI,pF,nF);
	fclose(yyin);
	return 0;
} 

//4. Given a input C file, replace all scanf with READ and printf with WRITE statements also find the 
//number of scanf and printf in the file.
%{
	int p=0;
    int s=0;
%}

%%
"printf" {p++; fprintf(yyout, "%s","READ");}
"scanf" {s++; fprintf(yyout, "%s","WRITE");}
. {fprintf(yyout, "%s", yytext);}
%%

int yywrap()
{
	return 1;
}

int main()
{
	yyin=fopen("input.txt","r");
    yyout=fopen("output.txt","w+");
	yylex();
	printf("Printf's : %d\nScanf's : %d\n",p,s);
	fclose(yyin);
    fclose(yyout);
	return 0;
} 

//5. That changes a number from decimal to hexadecimal notation.
%{
	unsigned int num;
%}

%%
[0-9]+ {num=atol(yytext);printf("%X\n",num);}
. {}
%%

int yywrap()
{
	return 1;
}

int main()
{
	yyin=fopen("input.txt","r");
	yylex();
	fclose(yyin);
	return 0;
} 

//6. Convert uppercase characters to lowercase characters of C file excluding the characters present in 
//the comment.
%{	
	#include<stdio.h>
%}

%%
"//"[A-Za-z" "]+\n {fprintf(yyout,"%s",yytext);}
"/*"[A-Za-z" "\n]+"*/" {fprintf(yyout,"%s",yytext);}
[A-Z] {fprintf(yyout,"%c",yytext[0]+32);}
. {fprintf(yyout,"%s",yytext);}
%%

int yywrap(){
	return 1;
}

int main(){
	yyin = fopen("input.txt","r");
	yyout = fopen("output.txt","w");
	yylex();
	fclose(yyin);
	fclose(yyout);
}

