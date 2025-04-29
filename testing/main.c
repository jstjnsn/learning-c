#include <stdio.h>

#include "counter.h"

int main()
{
    struct Counter *c = newCounter();
    printf("%d\n", value(c));

    increment(c);
    printf("%d\n", value(c));

    return 0;
}
