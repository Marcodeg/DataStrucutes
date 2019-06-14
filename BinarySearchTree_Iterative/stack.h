//
//  stack.h
//  ABR_I
//
//  Created by Marco Del Giudice N86001422.
//
//

#ifndef stack_h
#define stack_h

#include <stdio.h>

typedef struct stack {
    void * elem;
    struct stack * next;
}STACK;

typedef struct stackint {
    int elem;
    struct stack * next;
}STACKINT;


STACK *push (STACK *stack, void * val);
STACK *top (STACK *stack);
STACK *pop (STACK *stack);
STACK *SvuotaStack (STACK *stack);


#endif /* stack_h */
