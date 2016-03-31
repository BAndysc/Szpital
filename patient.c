#include <stdlib.h>
#include <string.h>
#include "patient.h"
#include "structure.h"

static Patient* newPatient(const char* name)
{
    Patient* patient = malloc(sizeof(Patient));

    patient->name = strdup(name);
    patient->diseases = newDiseaseList();

    return patient;
}


static void clearPatientData(Patient* patient)
{
    freeDiseaseList(patient->diseases);
    patient->diseases = newDiseaseList();
}

static void freePatient(Patient* patient)
{
    freeDiseaseList(patient->diseases);
    free(patient->name);
    free(patient);
}



const struct patients Patients = {
        .new = newPatient,
        .free = freePatient,
        .clearPatientData = clearPatientData
};