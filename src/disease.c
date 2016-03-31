#include <stdlib.h>
#include "disease.h"
#include "reference_string.h"

static Disease* newDisease(char const* description) {
    Disease* disease = malloc(sizeof(Disease));
    disease->description = ReferencedStrings.new(description);

    return disease;
}

static Disease* copyDisease(Disease* copy) {
    Disease* disease = malloc(sizeof(Disease));

    disease->description = copy->description;
    ReferencedStrings.incrementReferences(disease->description);

    return disease;
}

static void freeDisease(Disease* disease) {
    ReferencedStrings.dereference(disease->description);
    free(disease);
}

static void setDescriptionDisease(Disease* disease, char const* newDescription) {
    ReferencedStrings.dereference(disease->description);
    disease->description = ReferencedStrings.new(newDescription);
}

static void copyDiseaseDescription(Disease* destination, Disease* source) {
    ReferencedStrings.dereference(destination->description);

    destination->description = source->description;

    ReferencedStrings.incrementReferences(destination->description);
}




const struct diseases Diseases = {
    .new = newDisease,
    .free = freeDisease,
    .copyDisease = copyDisease,
    .setDescription = setDescriptionDisease,
    .copyDescription = copyDiseaseDescription
};