#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<ctype.h>
#include<string.h>
#include "init.h"
FILE *srcFile;
struct Token tkn;

void failure() {
    printf("Failed parsing for %s\n", tkn.lexeme);
    exit(1); 
}

void interfaceDecl();
void int_mode();
void ex_interfaces();
void ex_interfaces2();
void interf_body();
void int_mem_declarations();
void int_mem_declarations2();
void int_mem_dec();
void const_declarations();
void constid_list();
void constmod();
void type();
void interfaceType();
void constid_list2();
void constid_list3();

void interfaceDecl(){
    int_mode();
    if(strcmp(tkn.lexeme,"interface") != 0) failure();
    tkn = getNextToken(srcFile);
    if(tkn.type != IDENTIFIER) failure();
    tkn = getNextToken(srcFile);
    if(strcmp(tkn.lexeme,"extends") == 0) {
        tkn = getNextToken(srcFile);
        ex_interfaces();
    }
    interf_body();
}

void int_mode(){
    if(strcmp(tkn.lexeme,"public") == 0 || strcmp(tkn.lexeme,"private") == 0  || strcmp(tkn.lexeme,"abstract") == 0){
        tkn = getNextToken(srcFile);
        return;
    }else return;
}

void ex_interfaces(){
    interfaceType();
    ex_interfaces2();
}

void ex_interfaces2(){
    if(strcmp(tkn.lexeme,",") != 0) return;
    tkn = getNextToken(srcFile);
    if(tkn.type == IDENTIFIER){
        interfaceType();
        ex_interfaces2();
    }else failure();
}

void interf_body(){
    if(strcmp(tkn.lexeme,"{") != 0) failure();
    tkn = getNextToken(srcFile);
    int_mem_declarations();
    if(strcmp(tkn.lexeme,"}") != 0) failure();
    tkn = getNextToken(srcFile);
}


void int_mem_declarations(){
    int_mem_dec();
    int_mem_declarations2();
}

void int_mem_declarations2(){
    if(strcmp(tkn.lexeme,",")!=0) failure();
    tkn = getNextToken(srcFile);
    if(strcmp(tkn.lexeme,"public") == 0|| strcmp(tkn.lexeme,"static") == 0  || strcmp(tkn.lexeme,"final") == 0){
        int_mem_dec();
        int_mem_declarations2();
    }else return;
}

void int_mem_dec(){
    const_declarations();
}

void const_declarations(){
    if((strcmp(tkn.lexeme,"public") != 0 && strcmp(tkn.lexeme,"static") !=0  && strcmp(tkn.lexeme,"final") !=0)) return;
    constmod();
    type();
    constid_list();
    if(strcmp(tkn.lexeme,";") != 0) failure();
    tkn = getNextToken(srcFile);
    const_declarations();
}

void constid_list(){
    if(tkn.type != IDENTIFIER) failure();
    tkn = getNextToken(srcFile);
    constid_list2();
}

void constid_list2(){
    if(strcmp(tkn.lexeme,",") == 0) {
        tkn = getNextToken(srcFile);
        constid_list();
    } else if(strcmp(tkn.lexeme,"[") == 0) {
        tkn = getNextToken(srcFile);
        if(tkn.type != NUMBER) failure();
        tkn = getNextToken(srcFile);
        if(strcmp(tkn.lexeme,"]") != 0) failure();
        tkn = getNextToken(srcFile);
        constid_list3();
    }else return;
}


void constid_list3(){
        if(strcmp(tkn.lexeme,",") != 0) return;
        tkn = getNextToken(srcFile);
        constid_list();
}

void constmod(){
    if(strcmp(tkn.lexeme,"public") == 0|| strcmp(tkn.lexeme,"static") == 0 || strcmp(tkn.lexeme,"final") == 0){
        tkn = getNextToken(srcFile);
        return;
    }else return;
}

void type(){
    if(strcmp(tkn.lexeme,"int") == 0 || strcmp(tkn.lexeme,"float") == 0  || strcmp(tkn.lexeme,"Boolean") == 0){
        tkn = getNextToken(srcFile);
        return;
    }else return;
}

void interfaceType(){
    if(tkn.type == IDENTIFIER){
        tkn = getNextToken(srcFile);
        return;
    }else failure();
}


int main(){
    srcFile = fopen("test.txt","r");
    if(srcFile == NULL){
        exit(0);
    }
    tkn = getNextToken(srcFile);
    interfaceDecl();
    printf("Successful parse");
    return 0;
}