//
//  abr.c
//  LASD
//
//  Created by Marco Del Giudice N86001422.
//
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "abr.h"
#include "callback.h"

ABR *alloca_nodo(ABR *nodo) {
    nodo=(ABR*) malloc(sizeof(ABR));
    return nodo;
}

void dealloca_nodo (ABR *nodo){
    free(nodo);
}

ABR *inserisci(ABR *testa,void *valore, CMPDATA cmp, ALLOCA all)
{
    int confronto;
    if (testa == NULL){
        ABR *nodo=alloca_nodo(nodo);
        nodo->sx=NULL;
        nodo->dx=NULL;
        nodo->val = all(nodo->val, valore);
        testa=nodo;
    } else {
        confronto = cmp(testa->val , valore);
        if (confronto < 0){
            testa->dx = inserisci(testa->dx, valore, cmp,  all);
        }else if (confronto == 0){
            //non è possibile mettere due volte lo stesso valore!
        }
        else {
            testa->sx = inserisci (testa->sx , valore, cmp,  all);
        }
    }
    return testa;
}

void stampa_abr(ABR *testa, GETOUT stampa){
    if (testa!=NULL){
        stampa_abr(testa->sx, stampa);
        stampa(testa->val);
        stampa_abr(testa->dx, stampa);
    }
}

ABR *staccamin (ABR *testa, ABR *padre){
    if(testa != NULL) {
        if(testa->sx != NULL) {
            return staccamin(testa->sx, testa);
        } else {
            if(testa == padre->sx) {
                padre->sx = testa->dx;
            } else {
                padre->dx = testa->dx;
            }
        }
    }
    return testa;
}

void elimina_albero(ABR *testa, DEALLOCA deall){
    if (testa != NULL){
        elimina_albero(testa->sx, deall);
        elimina_albero(testa->dx, deall);
        deall(testa->val);
        dealloca_nodo(testa);
    }
}

ABR *cancella_radice(ABR *testa, ALLOCA all, DEALLOCA deall){
    if (testa != NULL){
        ABR *nodo=alloca_nodo(nodo);
        if (testa->sx != NULL && testa->dx !=NULL){
            nodo=staccamin(testa->dx, testa);
            testa->val=all(testa->val, nodo->val);
        }else {
            nodo=testa;
            if (testa->dx != NULL){
                testa=testa->dx;
            }else {
                testa=testa->sx;
            }
        }
        deall(nodo->val);
        dealloca_nodo(nodo);
    }
    return testa;
}

ABR *cancella(ABR *testa, void *valore, CMPDATA cmp ,ALLOCA all, DEALLOCA deall)
{
    if (testa != NULL){
        int confronto;
        confronto=cmp(valore, testa->val);
        if (confronto < 0){
            testa->sx = cancella(testa->sx,valore,cmp,all,deall);
        }else if (confronto>0){
            testa->dx = cancella(testa->dx,valore,cmp,all,deall);
        }else{
            testa=cancella_radice(testa, all, deall);
        }
    }
    return testa;
}

ABR *duplica (ABR *testa, ALLOCA all){
    if (testa != NULL){
        ABR *nuovo=alloca_nodo(nuovo);
        nuovo->val=all(nuovo->val, testa->val);
        nuovo->sx=duplica(testa->sx,all);
        nuovo->dx=duplica(testa->dx,all);
        return nuovo;
    }
    return testa;
}

int confronta_alberi (ABR *primo, ABR *secondo, CMPDATA cmp){
    if (primo == NULL && secondo == NULL){
        return 0;
    }
    else if (primo != NULL && secondo != NULL){
        if( cmp(primo->val, secondo->val)==0 && !confronta_alberi(primo->sx, secondo->sx, cmp) && !confronta_alberi(primo->dx, secondo->dx, cmp)){
            return 0;
        }else {
            return 1;
        }
        
    }else {
        return 1;
    }
}

void alloca_array (void **array, int c, void* valore, ALLOCA all){
    array[c]=all(array[c],valore);
}

int riempi_arrayord (ABR *testa, void **array, int c, ALLOCA all){
    if (testa!=NULL){
        c=riempi_arrayord(testa->sx, array, c, all);
        alloca_array(array, c, testa->val, all);
        return riempi_arrayord(testa->dx, array, c+1, all);
    }
    return c;
}

int conta_nodi (ABR* testa, int n){
    if (testa!=NULL){
        n=conta_nodi(testa->sx, n)+conta_nodi(testa->dx, n)+1;
    }
    return n;
}

ABR *bilancia (void **array, int inizio ,int fine, CMPDATA cmp, ALLOCA all){
    int medio;
    if (inizio >= fine || inizio <0 || fine <0){
        return NULL;
    }else {
        medio = (inizio+fine)/2;
        ABR *nodo = NULL;
        nodo=inserisci(nodo, array[medio], cmp , all);
        nodo->sx=bilancia(array, inizio, medio, cmp ,all);
        nodo->dx=bilancia(array, medio+1, fine, cmp ,all);
        return nodo;
    }
}

ABR *cancella_condizione(ABR *testa, void *a, void *b, int p, int p1, int p2, CMPDATA cmp, ALLOCA all, DEALLOCA deall){
    if (testa != NULL){
        int confronto1,confronto2;
        confronto1=cmp(testa->val, b);
        confronto2=cmp(testa->val, a);
        if (p <= p2){
            if (confronto2 < 0){
                testa->dx = cancella_condizione (testa->dx,a,b,p+1,p1,p2,cmp,all, deall);
            }else if (confronto1 > 0){
                testa->sx = cancella_condizione (testa->sx,a,b,p+1,p1,p2,cmp,all, deall);
            }else {
                testa->sx = cancella_condizione (testa->sx,a,b,p+1,p1,p2,cmp,all, deall);
                testa->dx = cancella_condizione (testa->dx,a,b,p+1,p1,p2,cmp,all, deall);
                if (p >= p1){
                    testa=cancella(testa, testa->val, cmp , all, deall);
                }
            }
        }
    }
    return testa;
}

int maxd (ABR* testa, COND cond){
    int x=0;
    if(testa!=NULL){
        int confronto;
        confronto=cond(testa->val);
        if(confronto==1 ){
            x= x + maxd(testa->sx, cond)+1;
            x= x + maxd(testa->dx, cond)+1;
        }else if(confronto ==0|| x>0 ){
            x= x + maxd(testa->sx, cond)+0;
            x= x + maxd(testa->dx, cond)+0;
            if(x>0){
                x= x + maxd(testa->sx, cond)+1;
                x= x + maxd(testa->dx, cond)+1;
            }
           
        }
    }
        return x;
}







