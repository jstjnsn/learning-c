#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef enum {
    OBJ_INT,
    OBJ_PAIR,
} ObjectType;

typedef struct sObject {
    ObjectType type;
    unsigned char marked;

    union {
        int value;

        struct {
            struct sObject* head;
            struct sObject* tail;
        };
    };
} Object;

#define STACK_MAX 256

typedef struct {
    Object* stack[STACK_MAX];
    int stackSize;
} VM;

VM* newVM() {
    VM* vm = malloc(sizeof(VM));
    vm->stackSize = 0;
    return vm;
}

void push(VM* vm, Object* value) {
    assert(vm->stackSize < STACK_MAX && "Stack overflow error!");
    vm->stack[vm->stackSize++] = value;
}

Object* pop(VM* vm) {
    assert(vm->stackSize > 0 && "Stack underflow error!");
    return vm->stack[--vm->stackSize];
}

Object* newObject(VM* vm, ObjectType type) {
    Object* object = malloc(sizeof(Object));
    object->type = type;
    return object;
}

void pushInt(VM* vm, int value) {
    Object* object = newObject(vm, OBJ_INT);
    object->value = value;
    push(vm, object);
}

Object* pushPair(VM* vm) {
    Object* object = newObject(vm, OBJ_PAIR);
    object->tail = pop(vm);
    object->head = pop(vm);

    push(vm, object);
    return object;
}

void mark(Object* object) {
    if (object->marked) return;

    object->marked = 1;

    if (object->type == OBJ_PAIR) {
        mark(object->head);
        mark(object->tail);
    }
}

void markAll(VM* vm) {
    for (int i = 0; i < vm->stackSize; i++) {
        mark(vm->stack[i]);
    }
}

void printStack(VM* vm) {
    for (int i = 0; i < vm->stackSize; i++) {
        Object* object = vm->stack[i];
        if (object->type == OBJ_INT) {
            printf("%d %d\n", object->type, object->value);
        } else if (object->type == OBJ_PAIR) {
            printf("%d %d %d\n", object->type, object->head->value, object->tail->value);
        }
    }
}

int main() {
    VM* vm = newVM();
    pushInt(vm, 1);
    pushInt(vm, 2);
    pushInt(vm, 3);
    pushPair(vm);
    printStack(vm);

    return 0;
}
