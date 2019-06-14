//
//  albero.c
//  HEAP
//
//  Created by Marco Del Giudice on 18/05/18.
//  Copyright © 2018 Marco Del Giudice. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "albero.h"
#include "heap.h"



TREE *alloca_nodo(TREE *nodo) {
    nodo=(TREE*) malloc(sizeof(TREE));
    return nodo;
}

unsigned int int_to_bin(unsigned int k) {
    return (k == 0 || k == 1 ? k : ((k % 2) + 10 * int_to_bin(k / 2)));
}

void libera(TREE *nodo){
    free(((COPPIA*)nodo->elem)->val);
    free(nodo->elem);
    free(nodo);
}
char *get_binary(unsigned int x) {
    char *s=malloc(sizeof(char)*12);
    int k=int_to_bin(x);
    sprintf(s, "%d", k);
    return s;
}

void riempi(TREE *nodo, void *coppia){
    nodo->elem=coppia;
    nodo->dx=NULL;
    nodo->sx=NULL;
}


TREE *inserimento(HEAP *heap, int i, COPPIA *coppia) {
    TREE* nodo=heap->elem;
    if(nodo==NULL){
        nodo=alloca_nodo(nodo);
        riempi(nodo,coppia);
        return nodo;
    }else{
        char *s=NULL;
        s=get_binary(i);
        int dim=(int)(strlen(s));
        dim=dim-1;
        int c=1;
        while(c<dim && nodo!=NULL){
            if(s[c]=='1'){
                nodo=nodo->dx;
            }else if(s[c]=='0'){
                nodo=nodo->sx;
            }
            c++;
        }
        if(s[dim]=='0'){
            nodo->sx=alloca_nodo(nodo->sx);
            riempi(nodo->sx, coppia);
        }else if(s[dim]=='1'){
            nodo->dx=alloca_nodo(nodo->dx);
            riempi(nodo->dx, coppia);
        }
        free(s);
        return heap->elem;
    }
}

void *get_el_tree(HEAP *heap, int i) {
    TREE* nodo=heap->elem;
    if(i <= 0 || i> heap->heapsize){
        return (COPPIA*)NULL;
    }else if(i==1){
        return nodo->elem;
    }
    else{
        char*s=get_binary(i);
        int dim=(int)(strlen(s));
        dim=dim-1;
        int c=1;
        while(c<=dim && nodo!=NULL){
            if(s[c]=='1'){
                nodo=nodo->dx;
            }else if(s[c]=='0'){
                nodo=nodo->sx;
            }
            c++;
    }
        free(s);
        return nodo->elem;
    }
}

void stampa_livello(TREE *nodo, int livello, HEAP *heap)
{
    if (nodo != NULL && livello == 0)
    {
        stampa_coppia(((COPPIA *)(nodo->elem)), heap);
    }
    else if (nodo != NULL)
    {
        stampa_livello(nodo->sx, livello - 1, heap);
        stampa_livello(nodo->dx, livello - 1, heap);
    }
}

int conta_livelli(TREE *nodo){
    int livelli=0;
    while(nodo->sx!=NULL){
        livelli++;
        nodo=nodo->sx;
    }
    return livelli;
}

void stampa_tree(HEAP *heap)
{
    if(heap->elem!=NULL){
        int livelli = conta_livelli(heap->elem);
        for (int i = 0; i <= livelli; i++)
        {
        stampa_livello(heap->elem, i, heap);
        }
    }
}

void cancella_foglia (HEAP *heap, int i){
    TREE* nodo=heap->elem;
    if(i==1 && heap->heapsize==0){
        libera(heap->elem);
        heap->elem=NULL;
        return ;
             
    }
    char*s=get_binary(i);
    int dim=(int)(strlen(s));
    dim=dim-1;
    int c=1;
    while(c<dim && nodo!=NULL){
        if(s[c]=='1'){
            nodo=nodo->dx;
        }else if(s[c]=='0'){
            nodo=nodo->sx;
        }
    c++;
    }
    if(s[dim]=='0'){
        libera(nodo->sx);
        nodo->sx=NULL;
    }else if(s[dim]=='1'){
        libera(nodo->dx);
        nodo->dx=NULL;
    }
    free(s);
    return ;
}




