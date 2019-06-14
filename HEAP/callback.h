//
//  callback.h
//  HEAP
//
//  Created by Marco Del Giudice on 11/05/18.
//  Copyright © 2018 Marco Del Giudice. All rights reserved.
//

#ifndef callback_h
#define callback_h
#include <stdio.h>

typedef void (*PRINT)(void*);
typedef void* (*GETELEM) (void*, int);
typedef int (*MINORMAX) (int , int);
typedef void* (*GETIN) (void);
typedef int (*CMPDATA) (void *, void*);
typedef void (*GETOUT) (void *);
typedef void* (*ALLOCA) (void *, void*);
typedef void (*DEALLOCA) (void*);

typedef struct nome {
    char* nome;
    char* cognome;
} NOME;

void CopiaDato(void *dest,int dpos, void *src,int spos, int dim);
int minore(int a, int b);
int maggiore(int a, int b);
//
void *GetInputInt(void);
void *GetRandomInt(void);
void *GetInputFloat (void);
void *GetRandomFloat (void);
void *GetInputString(void);
void *GetRandomString (void);
int CmpInt(void *a, void *b);
int CmpFloat(void *a, void *b);
int CmpString (void *a, void *b);
void StampaStringa(void *x);
void StampaFloat(void *x);
void StampaIntero(void *x);
void *AllocaStringa (void *nodo, void *stringa);
void *AllocaIntero (void *nodo, void *intero);
void *AllocaFl (void *nodo, void *fl);
void *GetInputStruct(void);
void *GetRandomStruct(void);
int CmpStruct(void *a, void *b);
void *GetRandomeStruct(void);
void StampaStruct (void *x);
void *AllocaStruct (void *nodo, void *nome);
void DeallocaElem (void *nodo);
void Deallocastruttura(void *s);
#endif /* callback_h */
