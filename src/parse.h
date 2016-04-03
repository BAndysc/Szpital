#ifndef HOSPITAL_PARSE_H
#define HOSPITAL_PARSE_H

#include <stdbool.h>

#define NEW_DISEASE_ENTER_DESCRIPTION "NEW_DISEASE_ENTER_DESCRIPTION"
#define NEW_DISEASE_COPY_DESCRIPTION "NEW_DISEASE_COPY_DESCRIPTION"
#define CHANGE_DESCRIPTION "CHANGE_DESCRIPTION"
#define PRINT_DESCRIPTION "PRINT_DESCRIPTION"
#define DELETE_PATIENT_DATA "DELETE_PATIENT_DATA"

#define MAX_COMMAND_LENGTH 30

#define ARGUMENT_SWITCH_DEBUG "-v"

typedef enum {
    PARSE_RESULT_OK,
    PARSE_RESULT_SILENT_OK,
    PARSE_RESULT_IGNORED,
    PARSE_RESULT_EOF,
} ParseResult;

typedef struct {
    char* name;
    char* diseaseDescription;
} DataEnterDescription;

typedef struct {
    char* sourceName;
    char* destinationName;
} DataCopyDescription;

typedef struct {
    char* name;
    int indexOfDisease;
    char* diseaseDescription;
} DataChangeDescription;

typedef struct {
    char* name;
    int indexOfDisease;
} DataPrintDescription;

typedef struct {
    char* name;
} DataDeletePatientData;

/*
 * Observer pattern "interface"
 */
typedef struct OnEventListener {
    ParseResult (*OnEnterDescription)(struct OnEventListener* this, DataEnterDescription* data);
    ParseResult (*OnCopyDescription)(struct OnEventListener* this, DataCopyDescription* data);
    ParseResult (*OnChangeDescription)(struct OnEventListener* this, DataChangeDescription* data);
    ParseResult (*OnPrintDescription)(struct OnEventListener* this, DataPrintDescription* data);
    ParseResult (*OnDeletePatientData)(struct OnEventListener* this, DataDeletePatientData* data);
} OnEventListener;


struct Parser;
typedef void (*OnParseResultCallback)(struct Parser* parser, ParseResult result);

typedef struct Parser {
    OnEventListener* listener;
    OnParseResultCallback parseResultCallback;
    bool debugMode;
} Parser;


/*
 * Parsers namespace
 */
struct parsers {
    Parser* (*new)(int argumentsCount, char** arguments);
    void (*free)(Parser* parser);

    ParseResult (*parse)(Parser* parser);

    void (*setEventListener)(Parser* parser, OnEventListener* listener);
    void (*setOnParseResultCallback)(Parser* parser, OnParseResultCallback callback);

    bool (*isDebugMode)(Parser* parser);

    void (*runParser)(Parser* parser);
};

const struct parsers Parsers;


#endif //HOSPITAL_PARSE_H
