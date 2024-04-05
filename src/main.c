#include "Rope.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    RopeString_t* string = RopeStringFromLiteral("   s  t  \n r i  n \t  g   ");
    RopeString_t* string2 = RopeStringFromLiteral("aaa");
    RopeString_t* string3 = RopeStringFromLiteral("test");
    RopeString_t* string4 = RopeTrimAll_n(string);
    RopePrint(string4);
    RopeDisposeString(string);
    RopeDisposeString(string2);
    RopeDisposeString(string3);
    RopeDisposeString(string4);
    return 0;
}