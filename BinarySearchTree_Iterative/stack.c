//
//  stack.c
//  ABR_I
//
//  Created by Marco Del Giudice N86001422.
//
//

#include "stack.h"
#include <stdlib.h>

STACK *push (STACK *stack, void * val){
    STACK *primo=malloc(sizeof(STACK));
    primo->elem=val;
    primo->next=stack;
    return primo;
}

STACK *top (STACK *stack){
    if(stack!=NULL){
        return stack->elem;
    }else{
        return NULL;
    }
}

STACK *pop (STACK *stack){
    if(stack==NULL){
        printf("ERRORE UNDERFLOW");
        return stack;
    }else {
        void *tmp=stack->next;
        free(stack);
        return tmp;
    }
}

STACK *SvuotaStack (STACK *stack){
    while(stack != NULL){
        stack=pop(stack);
    }
    return stack;
}
