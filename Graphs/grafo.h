//
//  grafo.h
//  GRAFI
//
//  Created by Marco Del Giudice on 22/05/18.
//  Copyright © 2018 Marco Del Giudice. All rights reserved.
//

#ifndef grafo_h
#define grafo_h

#include <stdio.h>
#include "callback.h"

typedef void (*SWAP) (void *, void*);

struct nodo_matrice {
    float peso;
    int conn;
};
typedef struct nodo_matrice MATRICE;


struct nodo_lista{
    void *val;
    float peso;
    struct nodo_lista *next;
};
typedef struct nodo_lista NODO_L;

struct vertice {
    void *val;
    //int indice;
};
typedef struct vertice VERTICE;

struct grafo {
    void ** adj; /**< Adjacency matrix. */
    int n; /**< Number of nodes in graph. */
    int matorlist;
    int tipo;
    int oriented;
    int negativew;
    VERTICE **vertici;
    GETIN getin;
    GETIN rnd;
    PRINT print;
    SWAP swap;
    ALLOCA all;
    CMPDATA cmp;
    
};
typedef struct grafo GRAFO;


GRAFO *alloca_grafo(GRAFO* g);
void *setta_vertice (int indice,GRAFO *g);
void stampa_vertice(GRAFO *g, void *v, int i);
void setta_arco(GRAFO *g);
void stampa_grafo(GRAFO *g);
GRAFO *imposta_grafo (int tipo, int matorlist, int oriented, GRAFO *g);
void aggiungi_vertice (GRAFO *g);
void cancella_arco (GRAFO *g,int src, int dst);
void stampa_array_vertici(GRAFO *g);
void cancella_vertice (GRAFO *g, int i);
void elimina_grafo(GRAFO *g);
void inizializza_grafo (GRAFO *g);
int *bfs (GRAFO *g, int src);
void percorso_minimo(GRAFO *g, int src,int path, int dst);
void stampa_percorso(GRAFO *g, int src, int dst, int* pres);
int *dfs (GRAFO *g);
NODO_L *ordinamento_top (GRAFO *g);
void stampa_ord_top(GRAFO *g,NODO_L *ord);
int dfs_aciclico (GRAFO *g);
int *dijkstra(GRAFO *g,int src);
void *bellman_ford (GRAFO *g, int src);
GRAFO *converti(GRAFO *g);
GRAFO *grafo_trasposto (GRAFO *g);
int *connected_components(GRAFO *g);
void massimo_sottografo(GRAFO*g);
void grafo_casuale (GRAFO *g,int n,int e);
#endif /* grafo_h */
