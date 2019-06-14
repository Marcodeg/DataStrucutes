//
//  callback.c
//  LASD
//
//  Created by Marco Del Giudice on 11/04/18.
//  Copyright © 2018 Marco Del Giudice. All rights reserved.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "callback.h"

char *leggistringa(){
    char c;
    char *str=malloc((sizeof(char))*20);
    int i=0;
    while ((read(0, &c, sizeof(c)) == sizeof(char)) && (c != '\n')) {
        str[i] = (char)c;
        i++;
    }
    str[i] = '\0';
    return str;
}

int condint (void *x){
    int a;
    a = *(int *)x;
    if(a%2==0){
        return 1;
    }
    return 0;
}

//CALLBACK PER GLI INTERI
void* GetInputInt () {
    int *intero;
    intero = malloc(sizeof(int));
    printf("Inserisci un valore intero: ");
    scanf("%d", intero);
    return intero;
}

void *GetRandomInt () {
    int *intero;
    intero = malloc(sizeof(int));
    *intero = rand()%100;
    return intero;
}

int CmpInt(void *a, void *b) {
    int na, nb;
    na = *(int *)a;
    nb = *(int *)b;
    if(na == nb) {
        return 0;
    } else if(na > nb) {
        return 1;
    } else {
        return -1;
    }
}

void StampaIntero(void *x) {
    if(x)
        printf("%d ", *((int *)x));
    else
        printf("NULL");
}

void *AllocaIntero (void *nodo, void *intero){
    nodo=(void*)malloc(sizeof(int));
    memcpy(nodo, intero, sizeof(int));
    return nodo;
}
//CALLBACK PER I FLOAT
void *GetInputFloat (){
    float *fl=(float*)malloc(sizeof(float));
    printf("Inserisci un valore float: ");
    scanf("%f", fl);
    return fl;
}

void *GetRandomFloat () {
    float *fl;
    fl = malloc(sizeof(float));
    float d = (float)rand()/(float)RAND_MAX;
    *fl = (rand()%100) + d;
    return fl;
}

int CmpFloat(void *a, void *b) {
    float na, nb;
    na = *(float *)a;
    nb = *(float *)b;
    if(na == nb) {
        return 0;
    } else if(na > nb) {
        return 1;
    } else {
        return -1;
    }
}

void StampaFloat(void *x) {
    if(x)
        printf("%f ", *(float*)x);
    else
        printf("NULL");
}

void *AllocaFl (void *nodo, void *fl){
    nodo= (void*)malloc(sizeof(float));
    memcpy(nodo, fl, sizeof(float));
    return nodo;
}

//CALLBACK PER LE STRINGHE


void *GetInputString() {
    printf("Inserisci una stringa: ");
    char *c;
    c=leggistringa();
    return (void*)c;
}

int CmpString (void *a, void *b) {
    return strcmp((char *)a, (char *)b);
}

void *GetRandomString () {
    int size=1+(rand () % (20-1+1));
    char* str=malloc((sizeof(char))*size);
    for (int j=0;j<size;j++){
        str[j]=97 + (rand()%(122-97+1));
    }
    str[size]='\0';
    return str;
}

void StampaStringa(void *x) {
    if(x)
        printf("%s ", (char *)x);
    else
        printf("NULL");
}

void *AllocaStringa (void *nodo, void *stringa){
    nodo=(char*)malloc((sizeof(char)*(strlen(stringa)))+1);
    strcpy(nodo,stringa);
    return nodo;
}


//CALLBACK PER LA STRUTTURA

void *GetInputStruct() {
    NOME *pers=malloc(sizeof(NOME));
    printf("Inserisci Nome \n");
    pers->nome=GetInputString();
    printf("Inserisci Cognome \n");
    pers->cognome=GetInputString();
    return pers;
}

int CmpStruct(void *a, void *b){
    int confronto;
    confronto=strcmp((*(NOME*)a).nome, (*(NOME*)b).nome);
    if(confronto == 0){
        return strcmp((*(NOME*)a).cognome, (*(NOME*)b).cognome);
    }else{
        return confronto;
    }
}

void *GetRandomStruct() {
    NOME *pers=malloc(sizeof(NOME));
    pers->nome=GetRandomString();
    pers->cognome=GetRandomString();
    return pers;
}

void StampaStruct (void *x){
    char *nomex,*cognomex;
    nomex=(*(NOME*)x).nome;
    cognomex=(*(NOME*)x).cognome;
    StampaStringa(nomex);
    StampaStringa(cognomex);
}

void *AllocaStruct (void *nodo, void *nome){
    nodo=(void*)malloc(sizeof(NOME));
    ((NOME *)nodo)->nome=AllocaStringa(((NOME *)nodo)->nome, ((NOME *)nome)->nome);
    ((NOME *)nodo)->cognome=AllocaStringa(((NOME *)nodo)->cognome, ((NOME *)nome)->cognome);
    return nodo;
}

void Deallocastruttura(void *s){
        free(((NOME*)s)->nome);
        free(((NOME*)s)->cognome);
}

void DeallocaElem (void *nodo){
    free(nodo);
}












