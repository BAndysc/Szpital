#include <stdlib.h>
#include <stdio.h>
#include "parse.h"
#include "helpers.h"

static Parser* newParser(int argumentsCount, char** arguments) {
    Parser* parser = calloc(1, sizeof(Parser));

    if (argumentsCount == 2)
        if (stringsEqual(arguments[1], ARGUMENT_SWITCH_DEBUG))
            parser->debugMode = true;

    return parser;
}

static void freeParser(Parser* parser) {
    free(parser);
}

static void setEventListener(Parser* parser, OnEventListener* listener) {
    parser->listener = listener;
}

static ParseResult executeCommandEnterDescription(Parser* parser, char* name, char* description) {
    autofree DataEnterDescription* data = malloc(sizeof(DataEnterDescription));

    data->diseaseDescription = description;
    data->name = name;

    if (parser->listener)
        return parser->listener->OnEnterDescription(parser->listener, data);
    return PARSE_RESULT_IGNORED;
}

static ParseResult parseCommandEnterDescription(Parser* parser) {
    autofree char* name = NULL;
    autofree char* disease = NULL;
    name = readSingleWord();
    disease = readLine();

    return executeCommandEnterDescription(parser, name, disease);
}


static ParseResult executeCommandCopyDescription(Parser* parser, char* sourceName, char* destinationName) {
    autofree DataCopyDescription* data = malloc(sizeof(DataCopyDescription));

    data->sourceName = sourceName;
    data->destinationName = destinationName;

    if (parser->listener)
        return parser->listener->OnCopyDescription(parser->listener, data);
    return PARSE_RESULT_IGNORED;
}

static ParseResult parseCommandCopyDescription(Parser* parser) {
    autofree char* sourceName = NULL;
    autofree char* destinationName = NULL;
    destinationName = readSingleWord();
    sourceName = readSingleWord();

    return executeCommandCopyDescription(parser, sourceName, destinationName);
}


static ParseResult executeCommandChangeDescription(Parser* parser, char* name, int index, char* diseaseDescription) {
    autofree DataChangeDescription* data = malloc(sizeof(DataChangeDescription));

    data->name = name;
    data->indexOfDisease = index;
    data->diseaseDescription = diseaseDescription;

    if (parser->listener)
        return parser->listener->OnChangeDescription(parser->listener, data);
    return PARSE_RESULT_IGNORED;
}

static ParseResult parseCommandChangeDescription(Parser* parser) {
    autofree char* name = NULL;
    autofree char* diseaseDescription = NULL;
    int index;
    name = readSingleWord();
    index = readInt();
    diseaseDescription = readLine();

    return executeCommandChangeDescription(parser, name, index, diseaseDescription);
}


static ParseResult executeCommandPrintDescription(Parser* parser, char* name, int index) {
    autofree DataPrintDescription* data = malloc(sizeof(DataPrintDescription));

    data->name = name;
    data->indexOfDisease = index;

    if (parser->listener)
        return parser->listener->OnPrintDescription(parser->listener, data);
    return PARSE_RESULT_IGNORED;
}

static ParseResult parseCommandPrintDescription(Parser* parser) {
    autofree char* name = NULL;
    int index;
    name = readSingleWord();
    index = readInt();

    return executeCommandPrintDescription(parser, name, index);
}


static ParseResult executeCommandDeletePatientData(Parser* parser, char* name) {
    DataDeletePatientData* data = malloc(sizeof(DataDeletePatientData));

    data->name = name;

    ParseResult result = PARSE_RESULT_IGNORED;

    if (parser->listener)
        result = parser->listener->OnDeletePatientData(parser->listener, data);
    free(data);
    return result;
}

static ParseResult parseCommandDeletePatientData(Parser* parser) {
    char* name = NULL;
    name = readSingleWord();

    ParseResult result = executeCommandDeletePatientData(parser, name);
    free(name);
    return result;
}



static ParseResult parseCommand(Parser* parser, char* command) {
    if (stringsEqual(NEW_DISEASE_ENTER_DESCRIPTION, command))
        return parseCommandEnterDescription(parser);

    else if (stringsEqual(NEW_DISEASE_COPY_DESCRIPTION, command))
        return parseCommandCopyDescription(parser);

    else if (stringsEqual(PRINT_DESCRIPTION, command))
        return parseCommandPrintDescription(parser);

    else if (stringsEqual(CHANGE_DESCRIPTION, command))
        return parseCommandChangeDescription(parser);

    else // if (stringsEqual(DELETE_PATIENT_DATA, command))
        return parseCommandDeletePatientData(parser);
}

static bool isDebugMode(Parser* parser) {
    return parser->debugMode;
}

static ParseResult parse(Parser* parser) {
    char input[MAX_COMMAND_LENGTH];
    if (scanf("%s ", input) != EOF)
        return parseCommand(parser, input);

    return PARSE_RESULT_EOF;
}


const struct parsers Parsers = {
    .new = newParser,
    .free = freeParser,
    .parse = parse,

    .setEventListener = setEventListener,

    .isDebugMode = isDebugMode
};