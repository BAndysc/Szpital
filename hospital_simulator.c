#include <stdio.h>
#include <stdlib.h>
#include "parse.h"
#include "patient.h"
#include "structure.h"
#include "disease.h"
#include "reference_string.h"
#include "hospital_simulator.h"


static ParseResult OnEnterDescription(Hospital* hospital, DataEnterDescription* data)
{
    Patient* patient = getPatientByName(hospital->patients, data->name);

    if (!patient)
    {
        patient = Patients.new(data->name);
        pushPatient(hospital->patients, patient);
    }

    pushDisease(patient->diseases, Diseases.new(data->diseaseDescription));
    return PARSE_RESULT_OK;
}

static ParseResult OnCopyDescription(Hospital* hospital, DataCopyDescription* data)
{
    Patient* patient = getPatientByName(hospital->patients, data->sourceName);
    Patient* patient2 = getPatientByName(hospital->patients, data->destinationName);

    if (!patient)
        return PARSE_RESULT_IGNORED;


    Disease* lastDisease = getDisease(patient->diseases, patient->diseases->size-1);

    if (!lastDisease)
        return PARSE_RESULT_IGNORED;

    if (!patient2)
    {
        patient2 = Patients.new(data->destinationName);
        pushPatient(hospital->patients, patient2);
    }

    Disease* newDisease = Diseases.copyDisease(lastDisease);
    pushDisease(patient2->diseases, newDisease);
    return PARSE_RESULT_OK;
}

static ParseResult OnChangeDescription(Hospital* hospital, DataChangeDescription* data)
{
    Patient* patient = getPatientByName(hospital->patients, data->name);

    if (!patient)
        return PARSE_RESULT_IGNORED;

    Disease* disease = getDisease(patient->diseases, data->indexOfDisease-1);

    if (!disease)
        return PARSE_RESULT_IGNORED;

    Diseases.setDescription(disease, data->diseaseDescription);
    return PARSE_RESULT_OK;
}

static ParseResult OnPrintDescription(Hospital* hospital, DataPrintDescription* data)
{
    Patient* patient = getPatientByName(hospital->patients, data->name);

    if (!patient)
        return PARSE_RESULT_IGNORED;

    Disease* disease = getDisease(patient->diseases, data->indexOfDisease-1);

    if (!disease)
        return PARSE_RESULT_IGNORED;

    printf("%s\n", disease->description->string);

    return PARSE_RESULT_SILENT_OK;
}

static ParseResult OnDeletePatientData(Hospital* hospital, DataDeletePatientData* data)
{
    Patient* patient = getPatientByName(hospital->patients, data->name);

    if (!patient)
        return PARSE_RESULT_IGNORED;

    Patients.clearPatientData(patient);

    return PARSE_RESULT_OK;
}

static void hookParserToHospital(Hospital* hospital, Parser* parser)
{
    Parsers.setOnEnterDescription(parser, &OnEnterDescription);
    Parsers.setOnCopyDescription(parser, &OnCopyDescription);
    Parsers.setOnChangeDescription(parser, &OnChangeDescription);
    Parsers.setOnPrintDescription(parser, &OnPrintDescription);
    Parsers.setOnDeletePatientData(parser, &OnDeletePatientData);
    Parsers.setHospital(parser, hospital);
}

static Hospital* newHospital()
{
    Hospital* hospital = malloc(sizeof(Hospital));
    hospital->patients = newPatientList();
    return hospital;
}

static void freeHospital(Hospital* hospital)
{
    freePatientList(hospital->patients);
    free(hospital);
}


const struct hospitals Hospitals = {
        .new = newHospital,
        .free = freeHospital,
        .hookParser = hookParserToHospital,
};