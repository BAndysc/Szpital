#include <stdio.h>
#include <stdlib.h>
#include "parse.h"
#include "patient.h"
#include "structure.h"
#include "disease.h"
#include "reference_string.h"
#include "hospital_simulator.h"
#include "helpers.h"

/*
 * The pointer to following struct can be safely casted to/from (OnEventListener*), because
 * struct OnEventListener is first field and C standard (C99: 6.7.2.1.5) guarantees
 * equivalence of memory layout
 *
 * More info in README.md
 */
typedef struct HospitalOnEventListener {
    OnEventListener base;
    Hospital* hospital;
} HospitalOnEventListener;

static Patient* getPatientByNameOrCreate(Hospital* hospital, char* name) {
    Patient* patient = PatientLists.getByName(hospital->patients, name);
    if (!patient) {
        patient = Patients.new(name);
        PatientLists.push(hospital->patients, patient);
    }
    return patient;
}

static ParseResult OnEnterDescription(OnEventListener* this, DataEnterDescription* data) {
    Hospital* hospital = CAST_POINTER(this, HospitalOnEventListener)->hospital;
    Patient* patient = getPatientByNameOrCreate(hospital, data->name);

    DiseaseLists.push(patient->diseases, Diseases.new(data->diseaseDescription));
    return PARSE_RESULT_OK;
}

static ParseResult OnCopyDescription(OnEventListener* this, DataCopyDescription* data) {
    Hospital* hospital = CAST_POINTER(this, HospitalOnEventListener)->hospital;
    Patient* patient = PatientLists.getByName(hospital->patients, data->sourceName);

    if (!patient)
        return PARSE_RESULT_IGNORED;

    Disease* lastDisease = DiseaseLists.getLast(patient->diseases);

    if (!lastDisease)
        return PARSE_RESULT_IGNORED;

    Patient* patient2 = getPatientByNameOrCreate(hospital, data->destinationName);

    DiseaseLists.push(patient2->diseases, Diseases.copyDisease(lastDisease));
    return PARSE_RESULT_OK;
}

static ParseResult OnChangeDescription(OnEventListener* this, DataChangeDescription* data) {
    Hospital* hospital = CAST_POINTER(this, HospitalOnEventListener)->hospital;
    Patient* patient = PatientLists.getByName(hospital->patients, data->name);

    if (!patient)
        return PARSE_RESULT_IGNORED;

    Disease* disease = DiseaseLists.get(patient->diseases, data->indexOfDisease-1);

    if (!disease)
        return PARSE_RESULT_IGNORED;

    Diseases.setDescription(disease, data->diseaseDescription);
    return PARSE_RESULT_OK;
}

static ParseResult OnPrintDescription(OnEventListener* this, DataPrintDescription* data) {
    Hospital* hospital = CAST_POINTER(this, HospitalOnEventListener)->hospital;
    Patient* patient = PatientLists.getByName(hospital->patients, data->name);

    if (!patient)
        return PARSE_RESULT_IGNORED;

    Disease* disease = DiseaseLists.get(patient->diseases, data->indexOfDisease-1);

    if (!disease)
        return PARSE_RESULT_IGNORED;

    printf("%s\n", disease->description->string);
    return PARSE_RESULT_SILENT_OK;
}

static ParseResult OnDeletePatientData(OnEventListener* this, DataDeletePatientData* data) {
    Hospital* hospital = CAST_POINTER(this, HospitalOnEventListener)->hospital;
    Patient* patient = PatientLists.getByName(hospital->patients, data->name);

    if (!patient)
        return PARSE_RESULT_IGNORED;

    Patients.clearPatientData(patient);

    return PARSE_RESULT_OK;
}

static HospitalOnEventListener* newHospitalOnEventListener(Hospital* hospital) {
    HospitalOnEventListener* listener = malloc(sizeof(HospitalOnEventListener));
    listener->hospital = hospital;
    listener->base.OnEnterDescription = OnEnterDescription;
    listener->base.OnCopyDescription = OnCopyDescription;
    listener->base.OnChangeDescription = OnChangeDescription;
    listener->base.OnPrintDescription = OnPrintDescription;
    listener->base.OnDeletePatientData = OnDeletePatientData;

    return listener;
}

static void hookParserToHospital(Hospital* hospital, Parser* parser) {
    OnEventListener* baseListener = (OnEventListener*)hospital->listeners;
    Parsers.setEventListener(parser, baseListener);
}

static Hospital* newHospital() {
    Hospital* hospital = malloc(sizeof(Hospital));
    hospital->patients = PatientLists.new();
    hospital->listeners = newHospitalOnEventListener(hospital);
    return hospital;
}

static void freeHospital(Hospital* hospital) {
    PatientLists.free(hospital->patients);
    free(hospital->listeners);
    free(hospital);
}


const struct hospitals Hospitals = {
    .new = newHospital,
    .free = freeHospital,
    .hookParser = hookParserToHospital,
};