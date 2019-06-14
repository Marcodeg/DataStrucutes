//
//  coda.c
//  GRAFI
//
//  Created by Marco Del Giudice on 02/06/18.
//  Copyright © 2018 Marco Del Giudice. All rights reserved.
//

#include "coda.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


CODA *accoda(CODA *c,void *val){
    CODA *tmp=c;
    CODA *nodo = malloc(sizeof(CODA));
    nodo->val=malloc(sizeof(int));
    nodo->next=NULL;
    memcpy(nodo->val, val, sizeof(int));
    if(tmp!=NULL){
        while(tmp->next!=NULL){
            tmp=tmp->next;
        }
        tmp->next=nodo;
        return c;
    }
    return nodo;
}

void *testa(CODA *c){
    if(c!=NULL){
        return c->val;
    }
    return NULL;
}

CODA *decoda(CODA *c){
    if(c!=NULL){
        CODA *tmp=c;
        c=c->next;
        free(tmp->val);
        free(tmp);
        return c;

    }
    return NULL;

}




