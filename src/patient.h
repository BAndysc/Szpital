#ifndef HOSPITAL_PATIENT_H
#define HOSPITAL_PATIENT_H

struct DiseaseList;

typedef struct Patient {
    char* name;
    struct DiseaseList* diseases;
} Patient;


/*
 * Patients namespace
 */
struct patients {
    Patient* (*new)(char const* name);
    void (*free)(Patient*);

    void (*clearPatientData)(Patient* patient);
};

const struct patients Patients;

#endif //HOSPITAL_PATIENT_H
