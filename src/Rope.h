#ifndef ROPE
#define ROPE

#include <stdlib.h>
#include <stdbool.h>

typedef struct RopeString {
    char* content;
    size_t length;
} RopeString_t;

typedef struct RopeIntArray {
    int* content;
    size_t length;
} RopeIntArray_t;

typedef struct RopeStringArray {
    RopeString_t** content;
    size_t length;
} RopeStringArray_t;

RopeString_t* RopeNewString(char* string, size_t stringLength);

RopeString_t* RopeStringFromLiteral(char* string);

void RopeDisposeString(RopeString_t* string);

RopeString_t* RopeCloneString(RopeString_t* string);

bool RopeStringsEqual(RopeString_t* string1, RopeString_t* string2);

char RopeCharAt(RopeString_t* string, size_t index);

bool RopeStartsWith(RopeString_t* string, RopeString_t* prefix);

bool RopeEndsWith(RopeString_t* string, RopeString_t* suffix);

bool RopeIncludes(RopeString_t* string, RopeString_t* substring);

bool RopeIsAlphabetic(RopeString_t* string);

bool RopeIsAlphanumeric(RopeString_t* string);

bool RopeIsNumber(RopeString_t* string);

int RopeFirstIndexOf(RopeString_t* string, RopeString_t* substring);

int RopeLastIndexOf(RopeString_t* string, RopeString_t* substring);

RopeIntArray_t* RopeAllIndicesOf(RopeString_t* string, RopeString_t* substring);

RopeString_t** RopeSplitAt(RopeString_t* string, size_t index);

RopeString_t* RopeRepeat_n(RopeString_t* string, size_t count);

RopeString_t* RopeRemoveSlice_n(RopeString_t* string, size_t startIndex, size_t endIndex);

RopeString_t* RopeRemoveFirst_n(RopeString_t* string, RopeString_t* target);

RopeString_t* RopeRemoveLast_n(RopeString_t* string, RopeString_t* target);

RopeString_t* RopeRemoveAll_n(RopeString_t* string, RopeString_t* target);

RopeString_t* RopeReplaceAt_n(RopeString_t* string, size_t index, size_t chars, RopeString_t* replacement);

RopeString_t* RopeReplaceFirst_n(RopeString_t* string, RopeString_t* target, RopeString_t* replacement);

RopeString_t* RopeReplaceLast_n(RopeString_t* string, RopeString_t* target, RopeString_t* replacement);

RopeString_t* RopeReplaceAll_n(RopeString_t* string, RopeString_t* target, RopeString_t* replacement);

RopeString_t* RopeInsertAt_n(RopeString_t* string, size_t index, RopeString_t* replacement);

RopeString_t* RopeSlice_n(RopeString_t* string, size_t startIndex, size_t endIndex);

RopeString_t* RopeConcat_n(RopeString_t* prefix, RopeString_t* suffix);

RopeString_t* RopeToLowerCase_n(RopeString_t* string);

RopeString_t* RopeToUpperCase_n(RopeString_t* string);

RopeString_t* RopeTrimStart_n(RopeString_t* string);

RopeString_t* RopeTrimEnd_n(RopeString_t* string);

RopeString_t* RopeTrimAll_n(RopeString_t* string);

void RopePrint(RopeString_t* string);

RopeIntArray_t* RopeNewIntArray(int* array, size_t arrayLength);

void RopeDisposeIntArray(RopeIntArray_t* array);

bool RopeIntArraysEqual(RopeIntArray_t* array1, RopeIntArray_t* array2);

RopeStringArray_t* RopeNewStringArray(RopeString_t** array, size_t arrayLength);

void RopeDisposeStringArray(RopeStringArray_t* array);

bool RopeStringArraysEqual(RopeStringArray_t* array1, RopeStringArray_t* array2);

#endif