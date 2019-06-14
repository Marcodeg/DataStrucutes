//
//  lista.h
//  LASD
//
//  Created by Marco Del Giudice N86001422.
//
//

#ifndef lista_h
#define lista_h
#include "abr.h"
struct list{
    char nome[20];
    int tipo;
    ABR *albero;
    struct list *next;
};
typedef struct list LISTA;

LISTA *estrai_lista(LISTA *lista, char *nome);
LISTA *inserisci_in_lista (LISTA *lista, char *valore, int tipo);
void stampa_lista (LISTA *lista);
LISTA *cancella_in_lista(LISTA *lista, char *valore);
#endif /* lista_h */

