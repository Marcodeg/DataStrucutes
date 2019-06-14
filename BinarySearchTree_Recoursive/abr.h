//
//  abr.h
//  LASD
//
//  Created by Marco Del Giudice N86001422.
//
//

#ifndef abr_h
#define abr_h
#include "callback.h"

struct abr_nodo{
    void *val;
    struct abr_nodo *sx;
    struct abr_nodo *dx;
};
typedef struct abr_nodo ABR;

//Prototipi
void stampa_abr(ABR *testa, GETOUT stampa);
ABR *inserisci(ABR *testa,void *valore, CMPDATA cmp, ALLOCA all);
void alloca_valore (ABR *nodo, char *valore);
void visualizza_stringa (char *str);
void dealloca_nodo (ABR *nodo);
ABR *alloca_nodo(ABR *nodo);
void elimina_albero(ABR *testa, DEALLOCA deall);
ABR *cancella(ABR *testa, void *valore, CMPDATA cmp ,ALLOCA all, DEALLOCA deall);
ABR *cancella_condizione(ABR *testa, void *a, void *b, int p, int p1, int p2, CMPDATA cmp, ALLOCA all, DEALLOCA deall);
ABR *duplica (ABR *testa, ALLOCA all);
int confronta_alberi (ABR *primo, ABR *secondo, CMPDATA cmp);
int riempi_arrayord (ABR *testa, void **array, int c, ALLOCA all);
int conta_nodi (ABR* testa, int n);
ABR *bilancia (void **array, int inizio ,int fine, CMPDATA cmp, ALLOCA all);
ABR *cancella_radice(ABR *testa, ALLOCA all, DEALLOCA deall);
int maxd (ABR* testa, COND cond);


#endif /* abr_h */

