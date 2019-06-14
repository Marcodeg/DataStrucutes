//
//  matrice.h
//  GRAFI
//
//  Created by Marco Del Giudice on 28/05/18.
//  Copyright © 2018 Marco Del Giudice. All rights reserved.
//

#ifndef matrice_h
#define matrice_h

#include <stdio.h>
#include "grafo.h"
void scambia_vertici_mat(void *x, void *y );
void ** alloca_matrice(int n);
void inizializza_matrice (GRAFO *g);
void stampa_matrice(GRAFO *g);
void setta_arco_matrice(GRAFO *g, int conn, int src, int dst, float peso);
MATRICE ** realloca_matrice(GRAFO *g);
void scambia_archi(MATRICE *x , MATRICE *y);
void dealloca_matrice (GRAFO *g);
void azzera_matrice(GRAFO *g);

#endif /* matrice_h */
