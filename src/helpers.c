#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "helpers.h"

void forceExitDueToArguments()
{
    printf(MESSAGE_UNKNOWN_ARGUMENTS);
    exit(EXIT_CODE_UKNOWN_ARGUMENTS);
}

static void skipWhitespaces() {
    int readChar;
    while ((readChar = getchar()) == ' ');
        ungetc(readChar, stdin);
}

static void expandCharArray(char** arrayToExpand, size_t size) {
    char* oldPointer = *arrayToExpand;
    *arrayToExpand = realloc(*arrayToExpand, size);

    if (!(*arrayToExpand)) {
        fprintf(stderr, ERROR_COULD_NOT_ALLOCATE_MEMORY);
        free(oldPointer);
        exit(EXIT_FAILURE);
    }
}

static void expandIfRequired(char** word, size_t* size,size_t newSize, int index) {
    if (index == *size) {
        *size = newSize;
        expandCharArray(word, *size);
    }
}

static void readPrintableUpTo(char** word, size_t* size, char charUpTo) {
    int readChar, index = 0;

    while ((readChar = getchar()) != EOF && isprint(readChar) && readChar != charUpTo) {
        expandIfRequired(word, size,(*size)*2, index);
        (*word)[index++] = (char)readChar;
    }
    expandIfRequired(word, size,*size+1, index);
    (*word)[index] = '\0';
}

static char* read(char charToSkip) {
    char* word;
    size_t wordSize;

    wordSize = DEFAULT_WORD_SIZE;
    word = malloc(wordSize);

    skipWhitespaces();
    readPrintableUpTo(&word, &wordSize, charToSkip);

    return word;
}

char* readSingleWord() {
    return read(' ');
}

char* readLine() {
    return read('\n');
}

int readInt() {
    int integer;
    scanf("%d", &integer);
    return integer;
}

bool stringsEqual(const char* string1, const char* string2) {
    return strcmp(string1, string2)==0;
}

char* stringDuplicate(const char* string)
{
    char* newString = malloc(strlen(string)+1);
    strcpy(newString, string);
    return newString;
}