//
//  lista.h
//  GRAFI
//
//  Created by Marco Del Giudice on 01/06/18.
//  Copyright © 2018 Marco Del Giudice. All rights reserved.
//

#ifndef lista_h
#define lista_h

#include <stdio.h>
void setta_arco_lista(GRAFO *g, int conn, int src, int dst, float peso);
void inizializza_lista (GRAFO *g);
void stampa_lista (GRAFO *g);
void stampa_nodo_l (NODO_L *nodo, GRAFO *g);
void dealloca_arco(NODO_L *nodo);
void cancella_arco_list(GRAFO *g,int src,int dst);
void scambia_vertici_lista(void *x, void *y );
NODO_L *cancella_lista(NODO_L* lista, void *val, GRAFO *g);

#endif /* lista_h */
