//
//  lista.c
//  LASD
//
//  Created by Marco Del Giudice on 15/03/18.
//
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"
#include "abr.h"


LISTA *inserisci_in_lista (LISTA *lista, char *valore, int tipo) {
    
    LISTA *nodo = malloc(sizeof(LISTA));
    strcpy(nodo->nome, valore);
    nodo->tipo=tipo;
    nodo->albero=NULL;
    nodo->next=lista;
    return nodo;
}

LISTA *estrai_lista(LISTA *lista, char *nome) {
    if(lista != NULL) {
        int confronto;
        confronto=strcmp(lista->nome,nome);
        if(confronto == 0) {
            return lista;
        }else {
            return estrai_lista(lista->next, nome);
        }
    }
    else{
        return NULL;
    }
}

void stampa_lista (LISTA *lista){
    if(lista!=NULL){
        printf("%s ",lista->nome);
        if (lista->tipo==0){
            printf("- intero\n");
        }else if (lista->tipo==1){
            printf("- float\n");
        }else if (lista->tipo==2){
            printf("- string\n");
        }else {
            printf("- struct\n");
        }
        stampa_lista(lista->next);
    }
}
LISTA *cancella_in_lista(LISTA *lista, char *valore){
    if (lista!=NULL){
        if ((strcmp(lista->nome, valore))==0){
            LISTA *nodo=lista->next;
            free(lista);
            return nodo;
        }
        else {
            lista->next = cancella_in_lista(lista->next, valore);
        }
    }
    return lista;
}

