#include <stdio.h>

void print()
{
    printf("Output\n");
}

void (*funcPtr)() = &print;

funcPtr();

funcPtr = print;

funcPtr();

void main() {}
