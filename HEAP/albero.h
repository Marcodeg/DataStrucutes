//
//  albero.h
//  HEAP
//
//  Created by Marco Del Giudice on 18/05/18.
//  Copyright © 2018 Marco Del Giudice. All rights reserved.
//

#ifndef albero_h
#define albero_h

#include <stdio.h>
#include "heap.h"

struct albero {
    void *elem;
    struct albero *sx;
    struct albero *dx;
};
typedef struct albero TREE;
TREE *alloca_nodo(TREE *nodo);
void riempi(TREE *nodo, void *coppia);
void *get_el_tree(HEAP *heap, int i);
void stampa_tree(HEAP *heap);
void cancella_foglia (HEAP *heap, int i);
TREE *inserimento(HEAP *heap, int i, COPPIA *coppia);

#endif /* albero_h */
