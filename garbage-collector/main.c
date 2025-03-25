#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef enum {
    OBJ_INT,
    OBJ_PAIR,
} ObjectType;

typedef struct sObject {
    ObjectType type; // OBJ_INT
    unsigned char marked; // 0
    struct sObject* next; // obj->obj

    union {
        int value; // 3

        struct {
            struct sObject* head; // obj
            struct sObject* tail; // obj
        };
    };
} Object;

/**
 *          obj OBJ_PAIR  ->   obj OBJ_INT
 *          / \                 3
 *        obj  obj
 *         1    2
 */

#define STACK_MAX 256
#define INITIAL_GC_THRESHOLD 128

typedef struct {
    Object* stack[STACK_MAX]; // [obj1, obj2, obj3]
    Object* head; // obj1
    int length; // 3
    int max; // 0
    int index; // 3
} VM;

VM* newVM() {
    VM* vm = malloc(sizeof(VM));
    vm->index = 0;
    vm->head = NULL;
    vm->length = 0;
    vm->max = INITIAL_GC_THRESHOLD;
    return vm;
}

void push(VM* vm, Object* value) {
    assert(vm->index < STACK_MAX && "Stack overflow error!");
    vm->stack[vm->index++] = value;
}

Object* pop(VM* vm) {
    assert(vm->index > 0 && "Stack underflow error!");
    return vm->stack[--vm->index];
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
    for (int i = 0; i < vm->index; i++) {
        mark(vm->stack[i]);
    }
}

/**
 * vm->stack = [0x123, 0x124, 0x125]
 * [1, 2, 3]
 */

void sweep(VM* vm) {
    Object** object = &vm->head; // store address of vm head
    while(NULL != *object) { // dereference vm head address
        if (!(*object)->marked) {
            Object* unmarked = *object;
            *object = unmarked->next;
            free(unmarked);
        } else {
            (*object)->marked = 0;
            object = &(*object)->next;
        }
    }
}

void gc(VM* vm) {
    int length = vm->length;

    markAll(vm);
    sweep(vm);

    vm->max = vm->length * 2;
}

Object* newObject(VM* vm, ObjectType type) {
    if (vm->length == vm->max) gc(vm);

    Object* object = malloc(sizeof(Object));
    object->type = type;
    object->marked = 0;

    object->next = vm->head;
    vm->head = object;
    vm->length++;

    /**
     * vm
     * - stack
     *      [obj->vm.head]
     * - head->obj
     */

    return object;
}


void printStack(VM* vm) {
    for (int i = 0; i < vm->index; i++) {
        Object* object = vm->stack[i];
        if (object->type == OBJ_INT) {
            printf("%d %d\n", object->type, object->value);
        } else if (object->type == OBJ_PAIR) {
            printf("%d %d %d\n", object->type, object->head->value, object->tail->value);
        }
    }
    printf("--------------\n");
}

void pushInt(VM* vm, int value) {
    Object* object = newObject(vm, OBJ_INT);
    object->value = value;
    push(vm, object);
    printStack(vm);
}

Object* pushPair(VM* vm) {
    /**
     * 1. stack: 1, 2, 3
     * 2. stack: 1, object = [2, 3]
     * 3. stack = 1, [2, 3]
     */
    Object* object = newObject(vm, OBJ_PAIR);
    object->tail = pop(vm);
    object->head = pop(vm);

    push(vm, object);
    printStack(vm);
    return object;
}

void populateStack(VM* vm) {
    for (int i = 0; i < INITIAL_GC_THRESHOLD+1; i++) {
        pushInt(vm, i);
    }
}


int main() {
    VM* vm = newVM();

    populateStack(vm);
    gc(vm);

    return 0;
}
