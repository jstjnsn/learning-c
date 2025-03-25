#include <stdio.h>
#include <stdlib.h>

typedef struct sObject {
    struct sObject* next; // obj->obj
    int value;
} Object;

int main() {
    int x = 5;
    int* y = &x; // y is a pointer, holding the address of x.
    // int z = &x; z is an int, we can't store an address in an int.
    // int z = *x; x is an int so we can't dereference it.
    // int** z = &x; z is a pointer to a pointer, we can't store just one pointer in it.

    Object* b = malloc(sizeof(Object));
    b->value = 2;

    Object* a = malloc(sizeof(Object));
    a->value = 1;
    a->next = NULL;
    
    b->next = a;

    Object** z = &a; 

    printf("%d\n", x);
    printf("%p\n", y);
    printf("%s\n", *z);

    return 0;
}