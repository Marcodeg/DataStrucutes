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
#include "stack.h"

ABR *alloca_nodo(ABR *nodo) {
    nodo=(ABR*) malloc(sizeof(ABR));
    return nodo;
}

void dealloca_nodo (ABR *nodo){
    free(nodo);
    
}

ABR *inserisci(ABR *testa, void *valore, CMPDATA cmp, ALLOCA all) {
    ABR *cur, *padre, *nuovonodo;
    cur = testa;
    padre = NULL;
    while(cur != NULL) {
        padre = cur;
        if(cmp(cur->val, valore) < 0) {
            cur = cur->dx;
        } else if(cmp(cur->val, valore) > 0) {
            cur = cur->sx;
        } else {
            return testa;
        }
    }
    nuovonodo = alloca_nodo(nuovonodo);
    nuovonodo->val = all(nuovonodo->val, valore);
    nuovonodo->sx = NULL;
    nuovonodo->dx = NULL;
    if(padre != NULL) {
        if(cmp(padre->val, valore) < 0) {
            padre->dx = nuovonodo;
        } else {
            padre->sx = nuovonodo;
        }
        return testa;
    } else {
        return nuovonodo;
    }
}


void stampa_abr(ABR *testa, GETOUT stampa){
    STACK *st=NULL;
    ABR *nodo=testa;
    while (st != NULL || nodo != NULL){
        if (nodo !=NULL){
            st=push(st, nodo);
            nodo=nodo->sx;
        }
        else {
            nodo=top(st);
            st=pop(st);
            stampa(nodo->val);
            nodo=nodo->dx;
        }
    }
}


ABR *staccamin (ABR *testa, ABR *padre){
    if(testa !=NULL){
        while(testa->sx !=NULL){
            padre=testa;
            testa=testa->sx;
        }
        if (testa == padre->sx){
            padre->sx = testa->dx;
        } else {
            padre->dx = testa->dx;
        }
    }
    return testa;
}

void elimina_albero (ABR *testa, DEALLOCA deall){
    STACK *st=NULL;
    ABR *curr=testa;
    ABR *last=NULL;
    
    while(curr != NULL || st != NULL){
        if(curr != NULL){
            if(curr->dx != NULL){
                st=push(st, curr);
                curr=curr->dx;
            }else {
                if (curr->sx != NULL){
                    st=push(st, curr);
                    curr=curr->sx;
                }else {
                    last=curr;
                    curr=NULL;
                }
            }
        }
        else {
            curr=(ABR*)top(st);
            st=pop(st);
            if(curr->dx==last){
                deall((curr->dx)->val);
                dealloca_nodo(curr->dx);
                curr->dx=NULL;
            }else if (curr->sx==last){
                deall((curr->sx)->val);
                dealloca_nodo(curr->sx);
                curr->sx=NULL;
                last=curr;
                curr=NULL;
            }
        }
    }
    deall((testa)->val);
    dealloca_nodo(testa);
}


ABR *cancella_radice(ABR *testa, ALLOCA all, DEALLOCA deall){
    if (testa != NULL){
        ABR *nodo;
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

ABR *cancella(ABR *testa, void *valore, CMPDATA cmp ,ALLOCA all, DEALLOCA deall){
    ABR *padre=NULL;
    ABR* nodo;
    nodo=testa;
    int confronto;
    while (nodo != NULL && (confronto=cmp(nodo->val,valore))!=0){
        padre=nodo;
        if(confronto > 0){
            nodo=nodo->sx;
        }else {
            nodo=nodo->dx;
        }
    }
    if (nodo!= NULL){
        if (padre == NULL){
        testa=cancella_radice(nodo, all, deall);
        }else if (nodo==padre->sx){
            padre->sx=cancella_radice(nodo, all, deall);
        }else if (nodo!=padre->sx){
            padre->dx=cancella_radice(nodo, all, deall);
        }
    }
    return testa;    
}

ABR *duplica (ABR *testa, ALLOCA all){
    STACK *st=NULL;
    STACK *st2=NULL;
    ABR *ret = NULL;
    ABR *curr2=NULL;
    ABR *curr=testa;
    ABR *last=NULL;
    while(curr != NULL || st !=NULL){
        if (curr !=NULL){
            curr2=alloca_nodo(curr2);
            curr2->val=all(curr2->val, curr->val);
            curr2->dx=NULL;
            curr2->sx=NULL;
            if(curr->dx !=NULL){
                st=push(st, curr);
                st2=push(st2, curr2);
                curr=curr->dx;
                curr2=NULL;
            }else {
                if(curr->sx != NULL){
                    st=push(st, curr);
                    st2=push(st2, curr2);
                    curr=curr->sx;
                    curr2=NULL;
                }else{
                    ret=curr2;
                    last=curr;
                    curr=NULL;
                }
            }
        }else{
            curr=(ABR*)top(st);
            curr2=(ABR*)top(st2);
            st2=pop(st2);
            if(last == curr->dx){
                curr2->dx=ret;
                if(curr->sx!=NULL){
                    st2=push(st2, curr2);
                    curr=curr->sx;
                    curr2=NULL;
                    
                }else{
                    st=pop(st);
                    ret=curr2;
                    curr=NULL;
                }
            }else{
                curr2->sx=ret;
                ret=curr2;
                last=curr;
                curr=NULL;
                st=pop(st);
            }
        }
    }
    return curr2;
}

int confronta_alberi (ABR *primo, ABR *secondo, CMPDATA cmp){
    STACK *st = NULL;
    STACK *st2 = NULL;
    ABR *curr = primo;
    ABR *curr2 = secondo;
    int ret=0;
    while((curr != NULL || st != NULL) && ret == 0 ){
        if( curr != NULL && curr2 != NULL){
            ret = cmp(curr->val,curr2->val);
            st = push(st, curr);
            st2 = push(st2, curr2);
            curr = curr->sx;
            curr2 = curr2->sx;
        }else if(curr == NULL  && curr2 == NULL){
            curr = (ABR*) top(st);
            curr2 = (ABR*) top(st2);
            st = pop(st);
            st2 = pop(st2);
            curr = curr->dx;
            curr2 = curr2->dx;
        }else{
            ret = 1;
        }
    }
    return ret;
}
void alloca_array (void **array, int c, void* valore, ALLOCA all){
    array[c]=all(array[c],valore);
}

void riempi_arrayord (ABR *testa, void **array, int c, ALLOCA all) {
    STACK *st=NULL;
    ABR *curr=testa;
    while (st != NULL || curr != NULL){
        if (curr !=NULL){
            st=push(st, curr);
            curr=curr->sx;
        }
        else {
            curr=(ABR*)top(st);
            st=pop(st);
            alloca_array(array, c, curr->val, all);
            c++;
            curr=curr->dx;
        }
    }
}

int conta_nodi (ABR* testa, int n){
    STACK *st=NULL;
    ABR *curr=testa;
    while (st != NULL || curr != NULL){
        if (curr !=NULL){
            st=push(st, curr);
            curr=curr->sx;
        }
        else {
            curr=(ABR*)top(st);
            st=pop(st);
            n++;
            curr=curr->dx;
        }
    }
    return n;
}

ABR *bilancia (void **array, int inizio ,int fine, CMPDATA cmp, ALLOCA all){
    if(fine <=0){
        return NULL;
    }
        STACK *st1 = NULL;
        STACK *st2 = NULL;
        ABR* curr = NULL;
        int medio=0;
        int stop=fine;
        while(medio!=stop){
            if(inizio <= fine){
                medio=(inizio+fine)/2;
                curr=inserisci(curr, array[medio], cmp , all);
                st1=push(st1, fine);
                st2=push(st2, medio+1);
                fine=medio-1;
            }else{
                fine=top(st1);
                st1 = pop(st1);
                inizio=top(st2);
                st2 = pop(st2);
            }
        }
    st1 = pop(st1);
    st2 = pop(st2);
    return curr;
}

ABR *cancella_condizione (ABR * testa, void *a, void *b, int p, int p1, int p2, CMPDATA cmp, ALLOCA all, DEALLOCA deall){
    ABR *curr=testa;
    STACK *st=NULL;
    void *last=malloc(sizeof(curr->val));
    int confronto,confronto2;
    while(curr!=NULL || st!=NULL){
        if(curr!=NULL && p <= p2){
            confronto=cmp(curr->val,b);
            confronto2=cmp(curr->val,a);
            if(curr->dx!=NULL && (confronto2<0 || confronto <0)){
                st=push(st, curr);
                last=memcpy(last, curr->val, sizeof(curr->val));
                curr=curr->dx;
                p++;
            }else{
                if(curr->sx!=NULL && (confronto2>0)){
                    st=push(st, curr);
                    last=memcpy(last, curr->val, sizeof(curr->val));
                    curr=curr->sx;
                    p++;
                }else{
                    st=push(st, curr);
                    p++;
                    last=memcpy(last, curr->val, sizeof(curr->val));
                    curr=NULL;
                }
            }
        }else if (p>=p1){
                curr=(ABR *)top(st);
                st=pop(st);
                p--;
                confronto=cmp(curr->val,b);
                confronto2=cmp(curr->val,a);
                if((cmp(last,curr->val)>0)){
                    if(curr->sx!=NULL && (confronto2>0)){
                        st=push(st, curr);
                        curr=curr->sx;
                        p++;
                    }else{
                        if(confronto<=0 && confronto2>=0){
                            testa=cancella(testa, curr->val, cmp, all, deall);
                            curr=NULL;
                        }
                        else{
                            curr=NULL;
                        }
                    }
            }else{
                if(confronto<=0 && confronto2>=0){
                    testa=cancella(testa, curr->val, cmp, all, deall);
                    curr=NULL;
                }
                else{
                    curr=NULL;
                }
            }
    }
    }
    free(last);
    return testa;
}



