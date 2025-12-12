#include <iostream>

#include "Date.h"

struct A
{
    int value;
};

int main()
{
    Date date(23, 7, 2025);

    A* aptr = new A;
    
    (*aptr).value = 100;
    aptr->value = 200;
}
