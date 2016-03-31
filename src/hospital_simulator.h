#ifndef SZPITAL_HOSPITAL_SIMULATOR_H
#define SZPITAL_HOSPITAL_SIMULATOR_H

struct PatientList;
struct Parser;

struct HospitalOnEventListener;

typedef struct
{
    struct PatientList* patients;
    struct HospitalOnEventListener* listeners;
} Hospital;


/*
 * Hospitals namespace
 */
struct hospitals {
    Hospital* (*new)();
    void (*free)(Hospital*);

    void (*hookParser)(Hospital* hospital, struct Parser* parser);
};

const struct hospitals Hospitals;


#endif //SZPITAL_HOSPITAL_SIMULATOR_H
