#ifndef SZPITAL_DISEASE_H
#define SZPITAL_DISEASE_H

struct ReferencedString;

typedef struct Disease
{
    struct ReferencedString* description;
} Disease;



/*
 * Diseases namespace simulation
 * https://ejrh.wordpress.com/2012/01/24/namespaces-in-c/
 *
 * This also creates abstraction layer between interface and implementation
 * The same pattern is used in other header files
 */

struct diseases {
    Disease* (*new)(char const* name);
    void (*free)(Disease*);

    Disease* (*copyDisease)(Disease* disease);
    void (*setDescription)(Disease* disease, char const* newDescription);
    void (*copyDescription)(Disease* destination, Disease* source);
};

const struct diseases Diseases;

#endif //SZPITAL_DISEASE_H
