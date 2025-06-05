#include <assert.h>

#include "counter.h"

int main()
{
    struct Counter *c = newCounter();
    assert(c);
    assert(value(c) == 0);

    increment(c);
    assert(value(c) == 1);

    return 0;
}