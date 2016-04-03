#include <stdlib.h>
#include <string.h>
#include "helpers.h"
#include "reference_string.h"

static int ALLOCATED_REFERENCED_STRINGS = 0;

static ReferencedString* newReferencedString(char const* string) {
    ReferencedString* referencedString = malloc(sizeof(ReferencedString));

    referencedString->references = 1;
    referencedString->string = stringDuplicate(string);

    ALLOCATED_REFERENCED_STRINGS++;

    return referencedString;
}

static void freeReferencedString(ReferencedString* referencedString) {
    free(referencedString->string);
    free(referencedString);
    ALLOCATED_REFERENCED_STRINGS--;
}

static void incrementReferenceString(ReferencedString* referencedString) {
    referencedString->references++;
}

static void dereferenceReferencedString(ReferencedString* referencedString) {
    referencedString->references--;

    if (referencedString->references == 0)
        freeReferencedString(referencedString);
}

static int getAllocatedReferenceStringsCount() {
    return ALLOCATED_REFERENCED_STRINGS;
}

const struct referencedStrings ReferencedStrings = {
    .new = newReferencedString,
    .free = freeReferencedString,
    .dereference = dereferenceReferencedString,
    .incrementReferences = incrementReferenceString,
    .getAllocatedStringsCount = getAllocatedReferenceStringsCount
};