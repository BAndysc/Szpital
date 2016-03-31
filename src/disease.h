#ifndef SZPITAL_DISEASE_H
#define SZPITAL_DISEASE_H

struct ReferencedString;

typedef struct Disease
{
    struct ReferencedString* description;
} Disease;

struct diseases {
    Disease* (*new)(char const*);
    void (*free)(Disease*);

    Disease* (*copyDisease)(Disease* disease);
    void (*setDescription)(Disease* disease, char const* newDescription);
    void (*copyDescription)(Disease* destination, Disease* source);
};

const struct diseases Diseases;

#endif //SZPITAL_DISEASE_H
