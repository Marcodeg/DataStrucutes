//
//  lista.c
//  GRAFI
//
//  Created by Marco Del Giudice on 01/06/18.
//  Copyright © 2018 Marco Del Giudice. All rights reserved.
//

#include <stdlib.h>
#include <unistd.h>
#include "matrice.h"
#include "grafo.h"
#include "callback.h"
#include "lista.h"

void stampa_nodo_l (NODO_L *nodo, GRAFO *g){
    if(nodo!=NULL){
        printf("\n[ ");
        g->print(nodo->val);
        printf("] ");
    }else{
        printf("NULL");
    }
}

void stampa_arco_l (NODO_L *nodo, GRAFO *g){
    if(nodo!=NULL){
        printf("-> [ ");
        g->print(nodo->val);
        printf(" , %.2f ] ", nodo->peso);
    }else{
        printf("NULL");
    }
}

void scambia_vertici_lista(void *x, void *y ){
    NODO_L tmp=*(NODO_L*)x;
    *(NODO_L*)x=*(NODO_L*)y;
    *(NODO_L*)y=tmp;
}

void dealloca_nodo_lista(NODO_L *nodo, GRAFO *g){
    free(nodo->val);
    free(nodo);
}

void cancella_arco_list(GRAFO *g,int src,int dst){
    NODO_L *nodo=((NODO_L*)g->adj[src]);
    if(nodo->next==NULL){
        return;
    }
    while(g->cmp(nodo->next->val,((NODO_L*)g->adj[dst])->val)!=0){
        nodo=nodo->next;
    }
    if(nodo==NULL){
        return;
    }
    NODO_L *tmp=nodo->next->next;
    NODO_L *d=nodo->next;
    dealloca_nodo_lista(d, g);
    nodo->next=tmp;
}


NODO_L * setta_nodo(NODO_L *nodo,void *val,float peso){
    nodo=malloc(sizeof(NODO_L));
    nodo->val=val;
    nodo->peso=peso;
    nodo->next=NULL;
    return nodo;
}

void setta_arco_lista(GRAFO *g, int conn, int src, int dst, float peso){
    NODO_L *nodo=((NODO_L*)g->adj[src]);
    void *val=NULL;
    val=g->all(val,((NODO_L*)g->adj[dst])->val);
    while(nodo->next!=NULL && g->cmp(nodo->next->val,val)!=0){
        nodo=nodo->next;
    }
    if(nodo->next==NULL){
        nodo->next=setta_nodo(nodo->next, val, peso);
    }
}

void inizializza_lista (GRAFO *g){
    int n,e;
    printf("\nscegli il numero di vertici da inserire: ");
    scanf("%d",&n);
    g->n=n;
    g->adj=malloc(sizeof(NODO_L**)*n);
    for(int i=0;i<n;i++){
        g->adj[i]=setta_vertice(i, g);
    }
    if(g->n>0){
        printf("\nscegli il numero di archi da inserire: ");
        scanf("%d",&e);
        for(int j=0;j<e;j++){
            setta_arco(g);
        }
    }
}



void stampa_lista (GRAFO *g){
    NODO_L *nodo=NULL;
    for(int i=0;i<g->n;i++){
        stampa_nodo_l(g->adj[i], g);
        nodo=((NODO_L*)g->adj[i]);
        while(nodo->next!=NULL){
            stampa_arco_l(nodo->next, g);
            nodo=nodo->next;
        }
    }
    printf("\n");
}







