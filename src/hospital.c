#include <stdio.h>
#include "parse.h"
#include "reference_string.h"

static void parseResult(Parser *parser, ParseResult parseResult)
{
    if (parseResult == PARSE_RESULT_OK)
        printf("OK\n");

    else if (parseResult == PARSE_RESULT_IGNORED)
        printf("IGNORED\n");

    if (Parsers.isDebugMode(parser))
        fprintf(stderr, "DESCRIPTIONS: %d\n", ReferencedStrings.getAllocatedStringsCount());
}

static void runParser(Parser* parser)
{
    ParseResult result;
    while ((result = Parsers.parse(parser)) != PARSE_RESULT_EOF)
        parseResult(parser, result);
}

int main(int argc, char** argv)
{
    Hospital* hospital = Hospitals.new();
    Parser* parser = Parsers.new(argc, argv);

    Hospitals.hookParser(hospital, parser);

    runParser(parser);

    Parsers.free(parser);
    Hospitals.free(hospital);
    return 0;
}

