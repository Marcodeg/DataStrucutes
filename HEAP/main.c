//
//  main.c
//  HEAP
//
//  Created by Marco Del Giudice on 11/05/18.
//  Copyright © 2018 Marco Del Giudice. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "heap.h"

int setta_heap(HEAP *heap);
HEAP *inizializza_heap(HEAP *heap);
void stampa_menu1(int minormax);
void gestisci_menu1(int scelta, HEAP *heap);
int prendi_indice(HEAP *heap);


int main(int argc, const char * argv[]) {
    int minormax,scelta=1;
    HEAP *heap=NULL;
    heap=alloca_heap(heap);
    minormax=setta_heap(heap);
    heap=inizializza_heap(heap);
    build_heap(heap);
    while (scelta!=0){
        stampa_menu1(minormax);
        scanf("%d",&scelta);
        gestisci_menu1(scelta, heap);
    }
    return 0;
}
HEAP *inizializza_heap(HEAP *heap){
    int dim=0;
    printf("\nscegli il numero di elementi da inserire\n");
    scanf("%d",&dim);
    if(heap->arrayortree==1){
    heap=inizializza_heap_array(heap, dim);
    }else{
    heap=inizializza_heap_tree(heap, dim);
    }
    return heap;
}

int setta_heap(HEAP *heap) {
    int minormax, arrayortree, tipo;
    printf("\n___________________________________\n\n"
           "   Imposta l'heap da realizzare\n"
           "___________________________________\n\nscegli l'ordinamento\n\n1-MIN-HEAP\n2-MAX HEAP\n");
    scanf("%d",&minormax);
    printf("\nscegli come rappresentarlo\n\n1. ARRAY\n2. ALBERO\n");
    scanf("%d",&arrayortree);
    printf("\nscegli il tipo di valore da inserire\n\n1-intero       2-float\n3-stringa      4-struct\n");
    scanf("%d",&tipo);
    if(tipo<1 || tipo >4){
        printf("selezione tipo errata!");
    }
    imposta_heap(heap, tipo, arrayortree, minormax);
    return minormax;
}

void stampa_menu1(int minormax){
    printf("\n___________________________________\n\n"
           "immetti un carattere per scegliere\n"
           "___________________________________\n\n1-stampa coda");
    if(minormax==1){
        printf("\n2-visualizza minimo\n3-estrai minimo");
    }else{
        printf("\n2-visualizza massimo\n3-estrai massimo");
    }
    printf("\n4-decrementa chiave\n5-incrementa chiave\n6-inserisci chiave\n7-cancella chiave\n0-nessuna operazione\n\n");
}

void gestisci_menu1(int scelta, HEAP *heap){
    COPPIA *max;
    void *val;
    int i,p;
    switch(scelta){
        case 1:
            printf("\n___________________________________\n\n");
            stampa_heap(heap);
            printf("___________________________________\n\n");
            break;
        case 2:
            max=max_elem(heap);
            stampa_coppia(max, heap);
            break;
        case 3:
            estrai_max(heap);
            stampa_heap(heap);
            break;
        case 4:
            i=prendi_indice(heap);
            printf("scegli nuova priorità\n");
            scanf("%d",&p);
            decrease_key(heap, i, p);
            break;
        case 5:
            i=prendi_indice(heap);
            printf("scegli nuova priorità\n");
            scanf("%d",&p);
            increase_key(heap, i, p);
            break;
        case 6:
            val=heap->getin();
            printf("scegli  priorità\n");
            scanf("%d",&p);
            inserisci_chiave(heap,val,p);
            break;
        case 7:
            i=prendi_indice(heap);
            delate(heap, i);
            break;
        case 0:
            elimina_heap(heap);
            break;
        default:
            printf("errore input.. riprova\n");
            break;
    }
}

int prendi_indice(HEAP *heap){
    int ok=1;
    int i;
    printf("\n___________________________________\n\n");
    stampa_heap(heap);
    printf("___________________________________\n\n");
    while(ok==1){
        printf("scegli l'indice dell'elemento\n");
        scanf("%d",&i);
        if(i>heap->heapsize || i<=0){
            printf("\nindice non presente!\n");
        }else{
            ok=0;
        }
    }
    return i;
}

