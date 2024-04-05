#include "Rope.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

RopeIntArray_t* RopeNewIntArray(int* array, size_t arrayLength) {
    RopeIntArray_t* new = malloc(sizeof(*new));
    if (!new) {
        return NULL;
    }
    int* arrayCopy = malloc(sizeof(int) * arrayLength);
    if(!arrayCopy) {
        free(new);
        return NULL;
    }
    memcpy(arrayCopy, array, sizeof(int) * arrayLength);
    new->content = arrayCopy;
    new->length = arrayLength;
    return new;
}

void RopeDisposeIntArray(RopeIntArray_t* array) {
    free(array->content);
    free(array);
}

bool RopeIntArraysEqual(RopeIntArray_t* array1, RopeIntArray_t* array2) {
    if (array1->length != array2->length) {
        return false;
    }
    for (int i = 0; i < array1->length; i++) {
        if (array1->content[i] != array2->content[i]) {
            return false;
        }
    }
    return true;
}