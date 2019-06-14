//
//  array.h
//  HEAP
//
//  Created by Marco Del Giudice on 14/05/18.
//  Copyright © 2018 Marco Del Giudice. All rights reserved.
//

#ifndef array_h
#define array_h

#include <stdio.h>
#include "heap.h"




void *get_el_array(HEAP *heap, int i);
HEAP *realloca_heap_array(HEAP *ogg);

#endif /* array_h */
