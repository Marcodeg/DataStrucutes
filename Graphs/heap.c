//
//  heap.c
//  HEAP
//
//  Created by Marco Del Giudice on 11/05/18.
//  Copyright © 2018 Marco Del Giudice. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "array.h"
#include "albero.h"

int get_indice_heap(HEAP *heap, void *val) {
    int i;
    COPPIA *tmp;
    i = 1;
    while(i <= heap->heapsize) {
        tmp = heap->getelem(heap, i);
        if(tmp!=NULL) {
            if(heap->cmp(tmp->val,val) == 0)
                return i;
        }
        i++;
    }
    return -1;
}

void scambia( COPPIA *x, COPPIA *y ){
    COPPIA tmp=*x;
    *x=*y;
    *y=tmp;
}

HEAP *alloca_heap(HEAP* heap) {
    heap = malloc(sizeof(HEAP));
    return heap;
}

void imposta_heap(HEAP * heap, int tipo, int arrayortree, int minormax) {
    heap->tipo = tipo;
    heap->arrayortree = arrayortree;
    heap->minormax = minormax;
    switch(minormax) {
        case 1:
            heap->check = &minore;
            break;
        case 2:
            heap->check = &maggiore;
            break;
        default:
            break;
    }
    switch(arrayortree) {
        case 1:
            heap->getelem= (GETELEM)&get_el_array;
            break;
        case 2:
            heap->getelem = (GETELEM)&get_el_tree;

            break;
        default:
            break;
        }
    switch(tipo) {
        case 1:
            heap->print = &StampaIntero;
            heap->getin = &GetInputInt;
            heap->cmp = &CmpInt;

            break;
        case 2:
            heap->print = &StampaFloat;
            heap->getin = &GetInputFloat;
            heap->cmp = &CmpFloat;

            break;
        case 3:
            heap->print = &StampaStringa;
            heap->getin = &GetInputString;
            heap->cmp = &CmpString;

            break;
      
        case 4:
            heap->print = &StampaStruct;
            heap->getin = &GetInputStruct;
            heap->cmp = &CmpStruct;
            break;
        default:
            break;
    }
}

COPPIA *setta_coppia (HEAP *heap){
    COPPIA *tmp = (COPPIA*) malloc(sizeof(COPPIA));
    printf("\n\n[ VALORE ] ");
    tmp->val=heap->getin();
    printf("[ PRIORITA' ] ");
    printf("Inserisci un valore intero: ");
    scanf("%d", &tmp->p);
    return tmp;
}

HEAP *inizializza_heap_array(HEAP *heap, int dim) {
    int i=0;
    COPPIA **array;
    array = malloc(sizeof(COPPIA**) * (dim*2));
    heap->heapsize = dim;
    heap->lenght = dim*2;
    while(i<dim) {
        array[i] = setta_coppia(heap);
        i++;
    }
    heap->elem = array;
    return heap;
}

HEAP *inizializza_heap_tree(HEAP *heap, int dim){
    int i=0;
    TREE *albero=NULL;
    heap->heapsize = dim;
    heap->elem=albero;
    while(i<dim) {
        COPPIA *tmp = setta_coppia(heap);
        heap->elem=inserimento(heap,(i+1),tmp);
        i++;
    }
    return heap;
}

void stampa_heap(HEAP *heap) {
    if(heap->heapsize < 1) {
        printf("NULL");
        return;
    } else {
        if(heap->arrayortree == 1) {
            //STAMPA RAPPRESENTAZIONE ARRAY
            int i=1;
            while(i<=heap->heapsize) {
                printf("[%d] ", i);
                stampa_coppia(((COPPIA**)(heap->elem))[i-1], heap);
                i++;
            }
        } else {
           //STAMPA ALBERO PER LIVELLI
            stampa_tree(heap);
        }
    }
}

void stampa_coppia(COPPIA *coppia, HEAP *heap) {
    if(coppia != NULL) {
        printf("[ ");
        heap->print(coppia->val);
        printf(" | priorita %d ]\n", coppia->p);
    } else {
        printf("[ NULL ]\n");
    }
}

int sinistro(int i){
    return 2*i;
}

int destro (int i){
    return (2*i)+1;
}

void heapify (HEAP *heap, int i) {
    int sx, dx, m;
    COPPIA *left, *right, *current, *max;
    sx = sinistro(i);
    dx = destro(i);
    m = i;
    left = heap->getelem(heap, sx);
    right = heap->getelem(heap, dx);
    current = heap->getelem(heap, i);
    if(sx <= heap->heapsize){
        if(heap->check(left->p,current->p)==1) {
        m = sx;
        } else {
            m = i;
        }
    }
    max = heap->getelem(heap, m);
    if(dx <= heap->heapsize){
        if(heap->check(right->p,max->p)==1) {
            m = dx;
        }
    }
    if(m != i) {
        scambia(current, heap->getelem(heap, m));
        heapify(heap, m);
    }
}

void build_heap (HEAP *heap) {
        for( int i = (heap->heapsize/2); i > 0; i--){
            heapify( heap, i );
        }
}

COPPIA *max_elem(HEAP *heap){
    if(heap->heapsize < 1){
        return NULL;
    }
    return heap->getelem(heap,1);
}

void estrai_max (HEAP *heap) {
    if(heap->heapsize < 1){
        printf("ERRORE UNDERFLOW");
        return;
    }
    else{
        delate(heap, 1);
    }
}

void decrease_key(HEAP *heap, int i, int priorita){
    if(i>heap->heapsize || i<=0){
        printf("Indice non presente");
    }else{
        COPPIA *tmp;
        tmp = heap->getelem(heap, i);
        if ((heap->check(priorita,tmp->p))==1){
            printf("Errore stai incrementando");
        }else{
            ((COPPIA*)(heap->getelem(heap, i)))->p = priorita;
            heapify(heap, i);
        }
    }
}

void increase_key(HEAP *heap, int i, int priorita){
    if(i>heap->heapsize || i<=0){
        printf("Indice non presente");
    }else{
        COPPIA *tmp;
        tmp = heap->getelem(heap, i);
        if ((heap->check(priorita,tmp->p))==0){
            printf("Errore stai decrementando");
        }else{
            ((COPPIA*)(heap->getelem(heap, i)))->p = priorita;
            while(i>1 && heap->check(((COPPIA *) (heap->getelem(heap, i/2)))->p,((COPPIA *) (heap->getelem(heap, i)))->p)== 0){
                scambia(heap->getelem(heap,i),heap->getelem(heap, i/2));
                i=i/2;
            }
        }
    }
}

void inserisci_chiave(HEAP *heap, void *val , int p){
    heap->heapsize=heap->heapsize + 1;
    COPPIA *nuovo;
    nuovo=malloc(sizeof(COPPIA));
    nuovo->p=p;
    nuovo->val=val;
    if(heap->arrayortree==1){
        heap=realloca_heap_array(heap);
        ((COPPIA**)(heap->elem))[heap->heapsize-1]=nuovo;
    }
    else{
        heap->elem=inserimento(heap, heap->heapsize, nuovo);
    }
    int i=heap->heapsize;
    while(i>1 && heap->check(((COPPIA *) (heap->getelem(heap, i/2)))->p,((COPPIA *) (heap->getelem(heap, i)))->p)== 0){
        scambia(heap->getelem(heap,i),heap->getelem(heap, i/2));
        i=i/2;
    }
}

void delate(HEAP *heap, int i){
    if(heap->heapsize < 1){
        printf("ERRORE UNDERFLOW");
        return;
    }else{
        int p=i/2;
        COPPIA *tmp=heap->getelem(heap, i);
        COPPIA *last=heap->getelem(heap, heap->heapsize);
        COPPIA *padre=NULL;
        if(i!=1){
        padre=heap->getelem(heap, p);
        }
        scambia(tmp,last);
        heap->heapsize=heap->heapsize - 1;
        if(i == 1 || (heap->check(padre->p,tmp->p))==1) {
                heapify(heap, i);
        } else {
                while(i>1 && heap->check(padre->p,tmp->p)==0){
                    scambia(tmp, padre);
                    i=i/2;
                }
        }
        if(heap->arrayortree==2){
            cancella_foglia(heap, heap->heapsize+1);
        }else if(heap->arrayortree==1){
            free(last->val);
            free(last);
        }
    }
}

void elimina_heap(HEAP *heap) {
    if(heap==NULL)
        return;
    while(heap->heapsize > 0) {
        delate(heap, 1);
    }
    if(heap->elem!=NULL){
        free(heap->elem);
        heap->elem = NULL;
    }
    if(heap){
        free(heap);
    }
}


