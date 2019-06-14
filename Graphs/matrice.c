//
//  matrice.c
//  GRAFI
//
//  Created by Marco Del Giudice on 28/05/18.
//  Copyright © 2018 Marco Del Giudice. All rights reserved.
//

#include <stdlib.h>
#include <unistd.h>
#include "matrice.h"
#include "grafo.h"
#include "callback.h"
#include "grafo.h"

void scambia_vertici_mat(void *x, void *y ){
    VERTICE tmp=*(VERTICE*)x;
    *(VERTICE*)x=*(VERTICE*)y;
    *(VERTICE*)y=tmp;
}


void ** alloca_matrice(int n)
{
    void **a;
    int i=0;
    a=malloc(((sizeof(MATRICE**))*n));
    for(i=0; i<n; i++) {
        a[i] = (MATRICE *)malloc(((sizeof(MATRICE))*n));
    }
    return a;
}

MATRICE ** realloca_matrice(GRAFO *g)
{
    
    MATRICE **a=(MATRICE**)g->adj;
    int i=0;
    a=realloc(a, sizeof(MATRICE**)*(g->n));
    for(i=0; i<=g->n-2; i++) {
        a[i]=realloc(a[i], sizeof(MATRICE)*(g->n));
    }
    a[g->n-1]=(MATRICE *)malloc(((sizeof(MATRICE))*g->n));
    for(int i=0;i<g->n;i++){
            a[i][g->n-1].conn=0;
            a[i][g->n-1].peso=0;
        
    }
    for(int j=0;j<g->n;j++){
            a[g->n-1][j].conn=0;
            a[g->n-1][j].peso=0;
    }
    return a;
}

void azzera_matrice(GRAFO *g){
    MATRICE **adj=(MATRICE**)g->adj;
    for(int i=0;i<g->n;i++){
        for(int j=0;j<g->n;j++){
            adj[i][j].conn=0;
            adj[i][j].peso=0;
        }
    }
}

void inizializza_matrice (GRAFO *g) {
    int n,e;
    printf("\nscegli il numero di vertici da inserire: ");
    scanf("%d",&n);
    g->adj=alloca_matrice(n);
    g->n=n;
    azzera_matrice(g);
    g->vertici=malloc(sizeof(VERTICE**) * n);
    for(int i=0;i<n;i++){
        g->vertici[i]=setta_vertice(i, g);
    }
    if(g->n>0){
        printf("\nscegli il numero di vertici da inserire: ");
        scanf("%d",&e);
        for(int j=0;j<e;j++){
            setta_arco(g);
        }
    }
}

void stampa_matrice(GRAFO *g){
    MATRICE **adj=(MATRICE**)g->adj;
    for(int i=0;i<g->n;i++){
        for(int j=0;j<g->n;j++){
            printf(" [ %d , %.2f ] ",adj[i][j].conn,adj[i][j].peso);
        }
        printf("\n");
    }
}

void setta_arco_matrice(GRAFO *g, int conn, int src, int dst, float peso){
    MATRICE **adj=(MATRICE**)g->adj;
    if(adj[src][dst].conn!=conn){
        adj[src][dst].conn=conn;
        adj[src][dst].peso=peso;
    }
}

void scambia_archi(MATRICE *x , MATRICE *y){
    MATRICE tmp=*x;
    *x=*y;
    *y=tmp;
}













