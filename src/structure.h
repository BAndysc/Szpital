#ifndef SZPITAL_STRUCTURE_H
#define SZPITAL_STRUCTURE_H

struct Disease;
struct Patient;

typedef struct Patient Patient;
typedef struct Disease Disease;


typedef struct DiseaseNode {
    struct Disease* value;
    struct DiseaseNode* next;
    struct DiseaseNode* prev;
} DiseaseNode;

typedef struct DiseaseList {
    DiseaseNode* first;
    DiseaseNode* last;
    int size;
} DiseaseList;


typedef struct PatientNode {
    Patient* value;
    struct PatientNode* prev;
    struct PatientNode* next;
} PatientNode;

typedef struct PatientList {
    PatientNode* first;
    PatientNode* last;
    int size;
} PatientList;




/*
 * PatientLists namespace
 */
struct patientLists {
    PatientList* (*new)();
    void (*free)(PatientList* list);

    void (*push)(PatientList* list, Patient* patient);
    void (*remove)(PatientList* list, int index);
    Patient* (*getByName)(PatientList*, const char* name);
};

const struct patientLists PatientLists;

/*
 * DiseaseLists namespace
 */
struct diseaseLists {
    DiseaseList* (*new)();
    void (*free)(DiseaseList* list);

    void (*push)(DiseaseList* list, Disease* disease);
    void (*remove)(DiseaseList* list, int index);
    Disease* (*get)(DiseaseList*, int index);
    Disease* (*getLast)(DiseaseList*);
};

const struct diseaseLists DiseaseLists;


#endif //SZPITAL_STRUCTURE_H
