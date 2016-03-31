#include <stdio.h>
#include "parse.h"
#include "reference_string.h"
#include "hospital_simulator.h"


int main()
{
    Hospital* hospital = Hospitals.new();
    Parser* parser = Parsers.new();

    Hospitals.hookParser(hospital, parser);

    ParseResult parseResult;

    while ((parseResult = Parsers.parse(parser)) != PARSE_RESULT_EOF)
    {
        if (parseResult == PARSE_RESULT_OK)
            printf("OK\n");

        else if (parseResult == PARSE_RESULT_IGNORED)
            printf("IGNORED\n");

        fprintf(stderr, "DESCRIPTIONS: %d\n", ReferencedStrings.getAllocatedStringsCount());
    }


    Parsers.free(parser);
    Hospitals.free(hospital);
    return 0;
}

