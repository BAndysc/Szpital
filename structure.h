#ifndef SZPITAL_STRUCTURE_H
#define SZPITAL_STRUCTURE_H

struct Disease;
struct Patient;

typedef struct Patient Patient;
typedef struct Disease Disease;


typedef struct DiseaseNode
{
    struct Disease* value;
    struct DiseaseNode* next;
    struct DiseaseNode* prev;
} DiseaseNode;

typedef struct DiseaseList
{
    DiseaseNode* first;
    DiseaseNode* last;
    int size;
} DiseaseList;


typedef struct PatientNode
{
    Patient* value;
    struct PatientNode* prev;
    struct PatientNode* next;
} PatientNode;

typedef struct PatientList
{
    PatientNode* first;
    PatientNode* last;
    int size;
} PatientList;





PatientList* newPatientList();
void freePatientList(PatientList* list);
void removePatient(PatientList* list, int index);
Patient* getPatientByName(PatientList* list, char const* name);
void pushPatient(PatientList* list, Patient* patient);

DiseaseList* newDiseaseList();
void freeDiseaseList(DiseaseList* diseaseList);
void pushDisease(DiseaseList* diseaseList, Disease* disease);
void removeDisease(DiseaseList*, int index);
Disease* getDisease(DiseaseList*, int index);


#endif //SZPITAL_STRUCTURE_H
