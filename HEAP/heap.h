//
//  heap.h
//  HEAP
//
//  Created by Marco Del Giudice on 11/05/18.
//  Copyright © 2018 Marco Del Giudice. All rights reserved.
//

#ifndef heap_h
#define heap_h

#include <stdio.h>
#include "callback.h"

struct pair{
    void *val;
    int p;
};
typedef struct pair COPPIA;

struct heap {
    void *elem;
    int heapsize;
    int lenght;
    PRINT print;
    GETIN getin;
    GETELEM getelem;
    MINORMAX check;
    int tipo;
    int arrayortree;
    int minormax;
};
typedef struct heap HEAP;

void imposta_heap(HEAP * heap, int tipo, int arrayortree, int minormax);
HEAP *inizializza_heap_array(HEAP *heap, int dim);
void stampa_heap(HEAP *heap);
void stampa_coppia(COPPIA *coppia, HEAP *heap);
HEAP *alloca_heap(HEAP* heap);
void build_heap(HEAP *heap);
void heapify(HEAP *heap, int i);
COPPIA *max_elem(HEAP *heap);
void estrai_max (HEAP *heap);
void decrease_key(HEAP *heap, int i, int priorita);
void increase_key(HEAP *heap, int i, int priorita);
void inserisci_chiave(HEAP *heap, void *val , int p);
void delate(HEAP *heap, int i);
HEAP *inizializza_heap_tree(HEAP *heap, int dim);
void elimina_heap(HEAP *heap);
#endif /* heap_h */
