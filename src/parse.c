#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parse.h"
#include "helpers.h"

static Parser* newParser()
{
    Parser* parser = calloc(1, sizeof(Parser));

    return parser;
}

static void freeParser(Parser* parser)
{
    free(parser);
}


static void setParserHospital(Parser* parser, Hospital* hospital)
{
    parser->hospital = hospital;
}

static void setParserOnEnterDescription(Parser* parser, OnEnterDescriptionPointer function)
{
    parser->OnEnterDescription = function;
}

static void setParserOnCopyDescription(Parser* parser, OnCopyDescriptionPointer function)
{
    parser->OnCopyDescription = function;
}

static void setParserOnChangeDescription(Parser* parser, OnChangeDescriptionPointer function)
{
    parser->OnChangeDescription = function;
}

static void setParserOnPrintDescription(Parser* parser, OnPrintDescriptionPointer function)
{
    parser->OnPrintDescription = function;
}

static void setParserOnDeletePatientData(Parser* parser, OnDeletePatientDataPointer function)
{
    parser->OnDeletePatientData = function;
}





static ParseResult executeCommandEnterDescription(Parser* parser, char* name, char* description)
{
    autofree DataEnterDescription* data = malloc(sizeof(DataEnterDescription));

    data->diseaseDescription = description;
    data->name = name;

    if (parser->OnEnterDescription)
        return (*(parser->OnEnterDescription))(parser->hospital, data);
    return PARSE_RESULT_IGNORED;
}

static ParseResult parseCommandEnterDescription(Parser* parser)
{
    autofree char* name = NULL;
    autofree char* disease = NULL;
    name = readSingleWord();
    disease = readLine();

    return executeCommandEnterDescription(parser, name, disease);
}



static ParseResult executeCommandCopyDescription(Parser* parser, char* sourceName, char* destinationName)
{
    autofree DataCopyDescription* data = malloc(sizeof(DataCopyDescription));

    data->sourceName = sourceName;
    data->destinationName = destinationName;

    if (parser->OnCopyDescription)
        return (*(parser->OnCopyDescription))(parser->hospital, data);
    return PARSE_RESULT_IGNORED;
}

static ParseResult parseCommandCopyDescription(Parser* parser)
{
    autofree char* sourceName = NULL;
    autofree char* destinationName = NULL;
    destinationName = readSingleWord();
    sourceName = readSingleWord();

    return executeCommandCopyDescription(parser, sourceName, destinationName);
}



static ParseResult executeCommandChangeDescription(Parser* parser, char* name, int index, char* diseaseDescription)
{
    autofree DataChangeDescription* data = malloc(sizeof(DataChangeDescription));

    data->name = name;
    data->indexOfDisease = index;
    data->diseaseDescription = diseaseDescription;

    if (parser->OnChangeDescription)
        return (*(parser->OnChangeDescription))(parser->hospital, data);
    return PARSE_RESULT_IGNORED;
}

static ParseResult parseCommandChangeDescription(Parser* parser)
{
    autofree char* name = NULL;
    autofree char* diseaseDescription = NULL;
    int index;
    name = readSingleWord();
    index = readInt();
    diseaseDescription = readLine();

    return executeCommandChangeDescription(parser, name, index, diseaseDescription);
}




static ParseResult executeCommandPrintDescription(Parser* parser, char* name, int index)
{
    autofree DataPrintDescription* data = malloc(sizeof(DataPrintDescription));

    data->name = name;
    data->indexOfDisease = index;

    if (parser->OnPrintDescription)
        return (*(parser->OnPrintDescription))(parser->hospital, data);
    return PARSE_RESULT_IGNORED;
}

static ParseResult parseCommandPrintDescription(Parser* parser)
{
    autofree char* name = NULL;
    int index;
    name = readSingleWord();
    index = readInt();

    return executeCommandPrintDescription(parser, name, index);
}



static ParseResult executeCommandDeletePatientData(Parser* parser, char* name)
{
    autofree DataDeletePatientData* data = malloc(sizeof(DataDeletePatientData));

    data->name = name;

    if (parser->OnDeletePatientData)
        return (*(parser->OnDeletePatientData))(parser->hospital, data);
    return PARSE_RESULT_IGNORED;
}

static ParseResult parseCommandDeletePatientData(Parser* parser)
{
    autofree char* name = NULL;
    name = readSingleWord();

    return executeCommandDeletePatientData(parser, name);
}


static ParseResult parseCommand(Parser* parser, char* command)
{
    if (strcmp(NEW_DISEASE_ENTER_DESCRIPTION, command)==0)
        return parseCommandEnterDescription(parser);

    else if (strcmp(NEW_DISEASE_COPY_DESCRIPTION, command)==0)
        return parseCommandCopyDescription(parser);

    else if (strcmp(PRINT_DESCRIPTION, command)==0)
        return parseCommandPrintDescription(parser);

    else if (strcmp(CHANGE_DESCRIPTION, command)==0)
        return parseCommandChangeDescription(parser);

    else // if (strcmp(DELETE_PATIENT_DATA, command)==0)
        return parseCommandDeletePatientData(parser);
    return PARSE_RESULT_IGNORED;
}

static ParseResult parse(Parser* parser)
{
    char input[300];
    if (scanf("%s ", input) != EOF)
    {
        return parseCommand(parser, input);
    }
    return PARSE_RESULT_EOF;
}




const struct parsers Parsers =
{
    .new = newParser,
    .free = freeParser,
    .parse = parse,

    .setHospital = setParserHospital,
    .setOnEnterDescription = setParserOnEnterDescription,
    .setOnCopyDescription = setParserOnCopyDescription,
    .setOnChangeDescription = setParserOnChangeDescription,
    .setOnPrintDescription = setParserOnPrintDescription,
    .setOnDeletePatientData = setParserOnDeletePatientData,
};