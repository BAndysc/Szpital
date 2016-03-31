#ifndef SZPITAL_PARSE_H
#define SZPITAL_PARSE_H

#include <stdbool.h>
#include "hospital_simulator.h"

#define NEW_DISEASE_ENTER_DESCRIPTION "NEW_DISEASE_ENTER_DESCRIPTION"
#define NEW_DISEASE_COPY_DESCRIPTION "NEW_DISEASE_COPY_DESCRIPTION"
#define CHANGE_DESCRIPTION "CHANGE_DESCRIPTION"
#define PRINT_DESCRIPTION "PRINT_DESCRIPTION"
#define DELETE_PATIENT_DATA "DELETE_PATIENT_DATA"


typedef enum
{
    PARSE_RESULT_OK,
    PARSE_RESULT_SILENT_OK,
    PARSE_RESULT_IGNORED,
    PARSE_RESULT_EOF,
} ParseResult;


typedef struct
{
    char* name;
    char* diseaseDescription;
} DataEnterDescription;

typedef struct
{
    char* sourceName;
    char* destinationName;
} DataCopyDescription;

typedef struct
{
    char* name;
    int indexOfDisease;
    char* diseaseDescription;
} DataChangeDescription;

typedef struct
{
    char* name;
    int indexOfDisease;
} DataPrintDescription;

typedef struct
{
    char* name;
} DataDeletePatientData;


typedef ParseResult (*OnEnterDescriptionPointer)(Hospital* hospital, DataEnterDescription *);
typedef ParseResult (*OnCopyDescriptionPointer)(Hospital* hospital, DataCopyDescription *);
typedef ParseResult (*OnChangeDescriptionPointer)(Hospital* hospital, DataChangeDescription *);
typedef ParseResult (*OnPrintDescriptionPointer)(Hospital* hospital, DataPrintDescription *);
typedef ParseResult (*OnDeletePatientDataPointer)(Hospital* hospital, DataDeletePatientData *);


typedef struct Parser
{
    OnEnterDescriptionPointer OnEnterDescription;
    OnCopyDescriptionPointer OnCopyDescription;
    OnChangeDescriptionPointer OnChangeDescription;
    OnPrintDescriptionPointer OnPrintDescription;
    OnDeletePatientDataPointer OnDeletePatientData;
    Hospital* hospital;
} Parser;

struct parsers {
    Parser* (*new)();
    void (*free)(Parser* parser);

    ParseResult (*parse)(Parser* parser);

    void (*setHospital)(Parser* parser, Hospital* hospital);
    void (*setOnEnterDescription)(Parser* parser, OnEnterDescriptionPointer function);
    void (*setOnCopyDescription)(Parser* parser, OnCopyDescriptionPointer function);
    void (*setOnChangeDescription)(Parser* parser, OnChangeDescriptionPointer function);
    void (*setOnPrintDescription)(Parser* parser, OnPrintDescriptionPointer function);
    void (*setOnDeletePatientData)(Parser* parser, OnDeletePatientDataPointer function);
};

const struct parsers Parsers;


#endif //SZPITAL_PARSE_H
