#include "Rope.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    RopeString_t* string = RopeStringFromLiteral("string1aaaaa");
    RopeString_t* string2 = RopeStringFromLiteral("helpaaaaaaa");
    RopeString_t* string3 = RopeStringFromLiteral("test");
    RopeString_t* string4 = RopeConcat_n(string, string2);
    RopePrint(string4);
    RopeDisposeString(string);
    RopeDisposeString(string2);
    RopeDisposeString(string3);
    RopeDisposeString(string4);
    return 0;
}