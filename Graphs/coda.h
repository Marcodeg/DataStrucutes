//
//  coda.h
//  GRAFI
//
//  Created by Marco Del Giudice on 02/06/18.
//  Copyright © 2018 Marco Del Giudice. All rights reserved.
//

#ifndef coda_h
#define coda_h

#include <stdio.h>

struct coda {
    void *val;
    struct coda * next;
};
typedef struct coda CODA;

CODA *accoda(CODA *c,void *val);
void *testa(CODA *c);
CODA *decoda(CODA *c);
#endif /* coda_h */
