#ifndef SZPITAL_PATIENT_H
#define SZPITAL_PATIENT_H

struct DiseaseList;

typedef struct Patient
{
    char* name;
    struct DiseaseList* diseases;
} Patient;



struct patients {
    Patient* (*new)(char const* name);
    void (*free)(Patient*);

    void (*clearPatientData)(Patient* patient);
};

const struct patients Patients;

#endif //SZPITAL_PATIENT_H
