//
//  array.c
//  HEAP
//
//  Created by Marco Del Giudice on 14/05/18.
//  Copyright © 2018 Marco Del Giudice. All rights reserved.
//

#include "array.h"
#include "heap.h"
#include <stdlib.h>

void *get_el_array(HEAP *heap, int i) {
    if(i >= 0 && i<= heap->heapsize){
        i=i-1;
        COPPIA *tmp=((COPPIA**)(heap->elem))[i];
        if(tmp!=NULL){
            return tmp;
        }
    }
    return NULL;
}

HEAP *realloca_heap_array(HEAP *heap) {
    COPPIA **arr;
    if((heap->heapsize+1) >= heap->lenght) {
        heap->lenght = (heap->heapsize+1)*2;
        arr = ((COPPIA**)(heap->elem));
        arr = realloc(arr, sizeof(COPPIA*) * (heap->lenght));
        heap->elem = arr;
    }
    return heap;
}









