#include "rope.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

#define min(X,Y) (((X) < (Y)) ? (X) : (Y))

RopeString_t* RopeNewString(char* string, size_t stringLength) {
    RopeString_t* new = malloc(sizeof(*new));
    if (!new) {
        return NULL;
    }
    char* fixedString = malloc(sizeof(char) * (stringLength + 1));
    if (!fixedString) {
        free(new);
        return NULL;
    } 
    memcpy(fixedString, string, stringLength);
    fixedString[stringLength] = '\0';
    new->content = fixedString;
    new->length = stringLength;
    return new;
}

RopeString_t* RopeStringFromLiteral(char* string) {
    return RopeNewString(string, strlen(string));
}

void RopeDisposeString(RopeString_t* string) {
    free(string->content);
    free(string);
}

RopeString_t* RopeCloneString(RopeString_t* string) {
    return RopeNewString(string->content, string->length);
}

bool RopeStringsEqual(RopeString_t* string1, RopeString_t* string2) {
    if (string1->length != string2->length) {
        return false;
    }
    for (int i = 0; i < string1->length; i++) {
        if (string1->content[i] != string2->content[i]) {
            return false;
        }
    }
    return true;
}

char RopeCharAt(RopeString_t* string, size_t index) {
    if (index >= string->length) {
        return '\0';
    }
    return string->content[index];
}

bool RopeStartsWith(RopeString_t* string, RopeString_t* prefix) {
    if (prefix->length > string->length) {
        return false;
    }
    for (int i = 0; i < prefix->length; i++) {
        if (string->content[i] != prefix->content[i]) {
            return false;
        }
    }
    return true;
}

bool RopeEndsWith(RopeString_t* string, RopeString_t* suffix) {
    if (suffix->length > string->length) {
        return false;
    }
    int offset = string->length - suffix->length;
    for (int i = 0; i < suffix->length; i++) {
        if (string->content[offset + i] != suffix->content[i]) {
            return false;
        }
    }
    return true;
}

bool RopeIncludes(RopeString_t* string, RopeString_t* substring) {
    return RopeFirstIndexOf(string, substring) != -1;
}

bool RopeIsAlphabetic(RopeString_t* string) {
    for (int i = 0; i < string->length; i++) {
        if (!isalpha(string->content[i])) {
            return false;
        }
    }
    return true;
}

bool RopeIsAlphanumeric(RopeString_t* string) {
    for (int i = 0; i < string->length; i++) {
        if (!isalnum(string->content[i])) {
            return false;
        }
    }
    return true;
}

bool RopeIsNumber(RopeString_t* string) {
    int i = 0;
    if (string->content[0] == '-') {
        i++;
    }
    bool notSeenDecimal = true;
    for (; i < string->length; i++) {
        if (!isdigit(string->content[i])) {
            if (notSeenDecimal && (string->content[i] == '.')) {
                notSeenDecimal = false;
                continue;
            }
            return false;
        }
    }
    return true;
}

int RopeFirstIndexOf(RopeString_t* string, RopeString_t* substring) {
    if (substring->length > string->length) {
        return -1;
    }
    
    int i, j, broken = false;
    for (i = 0; i < string->length - substring->length + 1; i++) {
        for (j = 0; j < substring->length; j++) {
            if (string->content[i + j] != substring->content[j]) {
                broken = true;
                break;
            }
        }
        if (!broken) { 
            return i;
        }
        broken = false;
    }
    return -1;
}

int RopeLastIndexOf(RopeString_t* string, RopeString_t* substring) {
    if (substring->length > string->length) {
        return -1;
    }
    
    int i, j, broken = false;
    for (i = string->length - substring->length + 1; i >= 0; i--) {
        for (j = 0; j < substring->length; j++) {
            if (string->content[i + j] != substring->content[j]) {
                broken = true;
                break;
            }
        }
        if (!broken) { 
            return i;
        }
        broken = false;
    }
    return -1;
}

RopeIntArray_t* RopeAllIndicesOf(RopeString_t* string, RopeString_t* substring) {
    if (substring->length > string->length) {
        return NULL;
    }
    size_t* content = malloc(sizeof(size_t) * string->length);
    if (!content) {
        return NULL;
    }

    int i, j, broken = false;
    size_t length = 0;
    for (i = 0; i < string->length - substring->length + 1; i++) {
        for (j = 0; j < substring->length; j++) {
            if (string->content[i + j] != substring->content[j]) {
                broken = true;
                break;
            }
        }
        if (!broken) {
            content[length] = i;
            length++;
        }
        broken = false;
    }

    RopeIntArray_t* new = RopeNewIntArray(content, length);
    free(content);
    return new;
}

RopeString_t** RopeSplitAt(RopeString_t* string, size_t index) {
    RopeString_t** array = malloc(sizeof(*array) * 2);
    if (!array) {
        return NULL;
    } else if (index == 0) {
        array[0] = RopeNewString("", 0);
        array[1] = RopeCloneString(string);
        if (!array[0] || !array[1]) {
            free(array);
            return NULL;
        }
        return array;
    } else if (index >= string->length) {
        array[0] = RopeCloneString(string);
        array[1] = RopeNewString("", 0);
        if (!array[0] || !array[1]) {
            free(array);
            return NULL;
        }
        return array;
    }
    size_t length = index;
    char* content = malloc(sizeof(char) * string->length);
    if (!content) {
        return NULL;
    }
    memcpy(content, string->content, length);
    array[0] = RopeNewString(content, length);
    if (!array[0]) {
        free(array);
        free(content);
        return NULL;
    }
    length = string->length - index;
    memcpy(content, string->content + index, length);
    array[1] = RopeNewString(content, length);
    if (!array[1]) {
        RopeDisposeString(array[0]);
        free(array);
        free(content);
        return NULL;
    }
    free(content);
    return array;
}

RopeString_t* RopeRepeat_n(RopeString_t* string, size_t count) {
    if (count == 0) {
        return RopeNewString("", 0);
    }
    size_t length = string->length * count;
    char* repeatedString = malloc(sizeof(char) * length);
    if (!repeatedString) {
        return NULL;
    }
    for (int i = 0; i < count; i++) {
        memcpy(repeatedString + i * string->length, string->content, string->length);
    }
    RopeString_t* new = RopeNewString(repeatedString, length);
    free(repeatedString);
    return new;
}

RopeString_t* RopeRemoveSlice_n(RopeString_t* string, size_t startIndex, size_t endIndex) {
    if (startIndex > endIndex) {
        size_t temp = startIndex;
        startIndex = endIndex;
        endIndex = temp;
    }
    if (startIndex >= string->length) {
        return string;
    }
    if (endIndex >= string->length) {
        endIndex = string->length - 1;
    }
    size_t sliceLength = endIndex - startIndex + 1;
    size_t length = string->length - sliceLength;
    char* content = malloc(sizeof(char) * length);
    if (!content) {
        return NULL;
    }
    memcpy(content, string->content, startIndex);
    memcpy(content + startIndex, string->content + endIndex + 1, string->length - endIndex - 1);
    RopeString_t* new = RopeNewString(content, length);
    free(content);
    return new;
}

RopeString_t* RopeRemoveFirst_n(RopeString_t* string, RopeString_t* target) {
    size_t startIndex = RopeFirstIndexOf(string, target);
    if (startIndex == -1 || target->length == 0) {
        return string;
    }
    size_t endIndex = startIndex + target->length - 1;
    return RopeRemoveSlice_n(string, startIndex, endIndex);
}

RopeString_t* RopeRemoveLast_n(RopeString_t* string, RopeString_t* target) {
    size_t startIndex = RopeLastIndexOf(string, target);
    if (startIndex == -1 || target->length == 0) {
        return string;
    }
    size_t endIndex = startIndex + target->length;
    return RopeRemoveSlice_n(string, startIndex, endIndex);
}

RopeString_t* RopeRemoveAll_n(RopeString_t* string, RopeString_t* target) {
    RopeIntArray_t* indices = RopeAllIndicesOf(string, target);
    char* content = malloc(sizeof(char) * string->length);
    if (!content) {
        return NULL;
    }
    int i, j;
    bool broken = false;
    size_t length = 0;
    for (i = 0; i < string->length; i++) {
        for (j = 0; j < indices->length; j++) {
            if ((i >= indices->content[j]) && (i < (indices->content[j] + target->length))) {
                broken = true;
                break;
            }
        }
        if (!broken) {
            content[length] = string->content[i];
            length++;
        }
        broken = false;
    }
    RopeDisposeIntArray(indices);
    RopeString_t* new = RopeNewString(content, length);
    if (!new) {
        return NULL;
    }
    free(content);
    return new;
}

RopeString_t* RopeReplaceAt_n(RopeString_t* string, size_t index, size_t chars, RopeString_t* replacement) {
    if (index >= string->length) {
        return string;
    }
    chars = min(string->length - index, chars);
    size_t length = string->length - chars + replacement->length;
    char* content = malloc(sizeof(char) * length);
    if (!content) {
        return NULL;
    }
    memcpy(content, string->content, index);
    memcpy(content + index, replacement->content, replacement->length);
    memcpy(content + index + replacement->length, string->content + index + chars, string->length - index - chars);
    RopeString_t* new = RopeNewString(content, length);
    free(content);
    return new;
}

RopeString_t* RopeReplaceFirst_n(RopeString_t* string, RopeString_t* target, RopeString_t* replacement) {
    size_t index = RopeFirstIndexOf(string, target);
    if (index == -1 || target->length == 0) {
        return string;
    }
    return RopeReplaceAt_n(string, index, target->length, replacement);
}

RopeString_t* RopeReplaceLast_n(RopeString_t* string, RopeString_t* target, RopeString_t* replacement) {
    size_t index = RopeLastIndexOf(string, target);
    if (index == -1 || target->length == 0) {
        return string;
    }
    return RopeReplaceAt_n(string, index, target->length, replacement);
}

//TODO: this function is slow because I'm bad at this
RopeString_t* RopeReplaceAll_n(RopeString_t* string, RopeString_t* target, RopeString_t* replacement) {
    if (target->length == 0) {
        return string;
    }
    RopeString_t* new = RopeCloneString(string);
    RopeString_t* old;
    size_t index = RopeFirstIndexOf(new, target);
    while (index != -1) {
        old = new;
        new = RopeReplaceAt_n(new, index, target->length, replacement);
        RopeDisposeString(old);
        if (!new) {
            return NULL;
        }
        index = RopeFirstIndexOf(new, target);
    }
    return new;
}

RopeString_t* RopeInsertAt_n(RopeString_t* string, size_t index, RopeString_t* replacement) {
    index = min(string->length, index);
    size_t length = string->length + replacement->length;
    char* content = malloc(sizeof(char) * length);
    if (!content) {
        return NULL;
    }
    memcpy(content, string->content, index);
    memcpy(content + index, replacement->content, replacement->length);
    memcpy(content + index + replacement->length, string->content + index, string->length - index);
    RopeString_t* new = RopeNewString(content, length);
    free(content);
    return new;
}

RopeString_t* RopeSlice_n(RopeString_t* string, size_t startIndex, size_t endIndex) {
    if (startIndex > endIndex) {
        size_t temp = startIndex;
        startIndex = endIndex;
        endIndex = temp;
    }
    if (startIndex >= string->length) {
        return string;
    }
    if (endIndex >= string->length) {
        endIndex = string->length - 1;
    }
    size_t length = endIndex - startIndex + 1;
    char* content = malloc(sizeof(char) * length);
    memcpy(content, string->content + startIndex, length);
    RopeString_t* new = RopeNewString(content, length);
    free(content);
    return new;
}

RopeString_t* RopeConcat_n(RopeString_t* prefix, RopeString_t* suffix) {
    size_t length = prefix->length + suffix->length;
    char* content = malloc(sizeof(char) * length);
    if (!content) {
        return NULL;
    }
    memcpy(content, prefix->content, prefix->length);
    memcpy(content + prefix->length, suffix->content, suffix->length);
    RopeString_t* new = RopeNewString(content, length);
    free(content);
    return new;
}

RopeString_t* RopeToLowerCase_n(RopeString_t* string) {
    RopeString_t* new = RopeNewString(string->content, string->length);
    if (!new) {
        return NULL;
    }
    for (int i = 0; i < new->length; i++) {
        if (isupper(new->content[i])) {
            new->content[i] += 32;
        }
    }
    return new;
}

RopeString_t* RopeToUpperCase_n(RopeString_t* string) {
    RopeString_t* new = RopeNewString(string->content, string->length);
    if (!new) {
        return NULL;
    }
    for (int i = 0; i < new->length; i++) {
        if (islower(new->content[i])) {
            new->content[i] -= 32;
        }
    }
    return new;
}

RopeString_t* RopeTrimStart_n(RopeString_t* string) {
    int i, whitespaceCount = 0;
    for (i = 0; i < string->length; i++) {
        if (!isspace(string->content[i])) {
            break;
        }
        whitespaceCount++;
    }
    return RopeRemoveSlice_n(string, 0, whitespaceCount - 1);
}

RopeString_t* RopeTrimEnd_n(RopeString_t* string) {
    int i, whitespaceCount = 0;
    for (i = string->length - 1; i >= 0; i--) {
        if (!isspace(string->content[i])) {
            break;
        }
        whitespaceCount++;
    }
    return RopeRemoveSlice_n(string, string->length - whitespaceCount, string->length - 1);
}

RopeString_t* RopeTrimAll_n(RopeString_t* string) {
    size_t length = 0;
    char* content = malloc(sizeof(char) * string->length);
    for (int i = 0; i < string->length; i++) {
        if (!isspace(string->content[i])) {
            content[length] = string->content[i];
            length++;
        }
    }
    RopeString_t* new = RopeNewString(content, length);
    if (!new) {
        return NULL;
    }
    free(content);
    return new;
}

void RopePrint(RopeString_t* string) {
    printf("%s\n", string->content);
}