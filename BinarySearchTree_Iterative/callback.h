//
//  callback.h
//  LASD
//
//  Created by Marco Del Giudice N86001422.
//
//

#ifndef callback_h
#define callback_h

#include <stdio.h>


typedef struct nome {
    char* nome;
    char* cognome;
} NOME;


typedef void* (*GETIN) (void);
typedef int (*CMPDATA) (void *, void*);
typedef void (*GETOUT) (void *);
typedef void* (*ALLOCA) (void *, void*);
typedef void (*DEALLOCA) (void*);

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


