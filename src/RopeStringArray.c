#include "Rope.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

RopeStringArray_t* RopeNewStringArray(RopeString_t** array, size_t arrayLength) {
    RopeStringArray_t* new = malloc(sizeof(*new));
    if (!new) {
        return NULL;
    }

    RopeString_t** arrayCopy = malloc(sizeof(RopeString_t*) * arrayLength);
    if(!arrayCopy) {
        return NULL;
    }
    for (int i = 0; i < arrayLength; i++) {
        arrayCopy[i] = RopeCloneString(array[i]);
        if (!arrayCopy[i]) {
            return NULL;
        }
    }

    new->content = arrayCopy;
    new->length = arrayLength;

    return new;
}

void RopeDisposeStringArray(RopeStringArray_t* array) {
    free(array->content);
    free(array);
}

bool RopeStringArraysEqual(RopeStringArray_t* array1, RopeStringArray_t* array2) {
    if (array1->length != array2->length) {
        return false;
    }
    for (int i = 0; i < array1->length; i++) {
        if (!RopeStringsEqual(array1->content[i], array2->content[i])) {
            return false;
        }
    }
    return true;
}