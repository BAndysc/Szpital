#include <stdlib.h>
#include <stdio.h>
#include "parse.h"
#include "helpers.h"

static Parser* newParser(int argumentsCount, char** arguments) {
    Parser* parser = calloc(1, sizeof(Parser));

    if (argumentsCount == 2 && stringsEqual(arguments[1], ARGUMENT_SWITCH_DEBUG))
        parser->debugMode = true;
    else if (argumentsCount > 1)
        forceExitDueToArguments();

    return parser;
}

static void freeParser(Parser* parser) {
    free(parser);
}

static void setEventListener(Parser* parser, OnEventListener* listener) {
    parser->listener = listener;
}

static void setOnParseResultCallback(Parser* parser, OnParseResultCallback callback)
{
    parser->parseResultCallback = callback;
}

static ParseResult executeCommandEnterDescription(Parser* parser, char* name, char* description) {
    DataEnterDescription data;

    data.diseaseDescription = description;
    data.name = name;

    if (parser->listener)
        return parser->listener->OnEnterDescription(parser->listener, &data);
    return PARSE_RESULT_IGNORED;
}

static ParseResult parseCommandEnterDescription(Parser* parser) {
    char* name = readSingleWord();
    char* disease = readLine();

    ParseResult result = executeCommandEnterDescription(parser, name, disease);

    free(name);
    free(disease);
    return result;
}


static ParseResult executeCommandCopyDescription(Parser* parser, char* sourceName, char* destinationName) {
    DataCopyDescription data;

    data.sourceName = sourceName;
    data.destinationName = destinationName;

    if (parser->listener)
        return parser->listener->OnCopyDescription(parser->listener, &data);
    return PARSE_RESULT_IGNORED;
}

static ParseResult parseCommandCopyDescription(Parser* parser) {
    char* destinationName = readSingleWord();
    char* sourceName = readSingleWord();

    ParseResult result = executeCommandCopyDescription(parser, sourceName, destinationName);

    free(sourceName);
    free(destinationName);
    return result;
}


static ParseResult executeCommandChangeDescription(Parser* parser, char* name, int index, char* diseaseDescription) {
    DataChangeDescription data;

    data.name = name;
    data.indexOfDisease = index;
    data.diseaseDescription = diseaseDescription;

    if (parser->listener)
        return parser->listener->OnChangeDescription(parser->listener, &data);
    return PARSE_RESULT_IGNORED;
}

static ParseResult parseCommandChangeDescription(Parser* parser) {
    char* name = readSingleWord();
    int index = readInt();
    char* diseaseDescription = readLine();

    ParseResult result = executeCommandChangeDescription(parser, name, index, diseaseDescription);

    free(name);
    free(diseaseDescription);
    return result;
}


static ParseResult executeCommandPrintDescription(Parser* parser, char* name, int index) {
    DataPrintDescription data;

    data.name = name;
    data.indexOfDisease = index;

    if (parser->listener)
        return parser->listener->OnPrintDescription(parser->listener, &data);
    return PARSE_RESULT_IGNORED;
}

static ParseResult parseCommandPrintDescription(Parser* parser) {
    char* name = readSingleWord();
    int index = readInt();

    ParseResult result = executeCommandPrintDescription(parser, name, index);

    free(name);
    return result;
}


static ParseResult executeCommandDeletePatientData(Parser* parser, char* name) {
    DataDeletePatientData data;
    data.name = name;

    if (parser->listener)
        return parser->listener->OnDeletePatientData(parser->listener, &data);
    return PARSE_RESULT_IGNORED;
}

static ParseResult parseCommandDeletePatientData(Parser* parser) {
    char* name = readSingleWord();

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

static void callCallback(Parser* parser, ParseResult result) {
    if (parser->parseResultCallback)
        parser->parseResultCallback(parser, result);
}

static ParseResult parse(Parser* parser) {
    ParseResult result = PARSE_RESULT_EOF;
    char input[MAX_COMMAND_LENGTH];

    if (scanf("%s ", input) != EOF) {
        result = parseCommand(parser, input);
        callCallback(parser, result);
    }

    return result;
}

static void runParser(Parser* parser) {
    ParseResult result;
    do {
        result = Parsers.parse(parser);
    } while (result != PARSE_RESULT_EOF);
}

const struct parsers Parsers = {
    .new = newParser,
    .free = freeParser,
    .parse = parse,

    .setEventListener = setEventListener,
    .setOnParseResultCallback = setOnParseResultCallback,

    .isDebugMode = isDebugMode,
    .runParser = runParser
};