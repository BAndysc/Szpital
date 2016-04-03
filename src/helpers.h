#ifndef HOSPITAL_HELPERS_H
#define HOSPITAL_HELPERS_H

#include <stdbool.h>

#define ERROR_COULD_NOT_ALLOCATE_MEMORY "Couldn't allocate memory for a string\n"
#define DEFAULT_WORD_SIZE 16
#define MESSAGE_UNKNOWN_ARGUMENTS "ERROR"
#define EXIT_CODE_UKNOWN_ARGUMENTS 1

#define CAST_POINTER(A, B) ((B*)A)

void forceExitDueToArguments();
char* readSingleWord();
char* readLine();
int readInt();

bool stringsEqual(char* string1, char* string2);

#endif //HOSPITAL_HELPERS_H