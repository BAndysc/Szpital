#ifndef SZPITAL_REFERENCE_STRING_H
#define SZPITAL_REFERENCE_STRING_H


typedef struct ReferencedString
{
    int references;
    char* string;
} ReferencedString;


/*
 * ReferencedStrings namespace
 */
struct referencedStrings {
    ReferencedString* (*new)(char const* string);
    void (*free)(ReferencedString*);

    void (*dereference)(ReferencedString* referencedString);
    void (*incrementReferences)(ReferencedString* referencedString);

    int (*getAllocatedStringsCount)();
};

const struct referencedStrings ReferencedStrings;

#endif //SZPITAL_REFERENCE_STRING_H
