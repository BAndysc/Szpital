#include <stdio.h>
#include "parse.h"
#include "reference_string.h"
#include "hospital_simulator.h"

#define MESSAGE_OK "OK\n"
#define MESSAGE_IGNORED "IGNORED\n"
#define MESSAGE_DEBUG_DESCRIPTIONS "DESCRIPTIONS: %d\n"

static void parseResult(Parser* parser, ParseResult parseResult) {
    if (parseResult == PARSE_RESULT_OK)
        printf(MESSAGE_OK);
    else if (parseResult == PARSE_RESULT_IGNORED)
        printf(MESSAGE_IGNORED);

    if (Parsers.isDebugMode(parser))
        fprintf(stderr, MESSAGE_DEBUG_DESCRIPTIONS, ReferencedStrings.getAllocatedStringsCount());
}

int main(int argc, char** argv) {
    Parser* parser = Parsers.new(argc, argv);
    Hospital* hospital = Hospitals.new();

    Hospitals.hookParser(hospital, parser);
    Parsers.setOnParseResultCallback(parser, parseResult);

    Parsers.runParser(parser);

    Parsers.free(parser);
    Hospitals.free(hospital);
    return 0;
}

