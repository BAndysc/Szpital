#ifndef HOSPITAL_DISEASE_H
#define HOSPITAL_DISEASE_H

struct ReferencedString;

typedef struct Disease {
    struct ReferencedString* description;
} Disease;



/*
 * Diseases namespace simulation
 * https://ejrh.wordpress.com/2012/01/24/namespaces-in-c/
 *
 * This also creates abstraction layer between interface and implementation
 * The same pattern is used in other header files
 *
 * More info in README.md
 */

struct diseases {
    Disease* (*new)(char const* name);
    void (*free)(Disease*);

    Disease* (*copyDisease)(Disease* disease);
    void (*setDescription)(Disease* disease, char const* newDescription);
    void (*copyDescription)(Disease* destination, Disease* source);
};

const struct diseases Diseases;

#endif //HOSPITAL_DISEASE_H
