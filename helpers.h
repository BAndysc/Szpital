/* This code is public domain -- Will Hartung 4/9/09 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ERROR_COULD_NOT_ALLOCATE_MEMORY "Couldn't allocate memory for a string\n"

#define autofree __attribute__((cleanup(free_stack)))

__attribute__ ((always_inline))
inline void free_stack(void *ptr) {
    free(*(void **) ptr);
}

static void skipWhitespaces()
{
    int readChar;
    while ((readChar = getchar()) == ' ');
        ungetc(readChar, stdin);
}

static void expandCharArray(char** arrayToExpand, size_t size)
{
    char* oldPointer = *arrayToExpand;
    *arrayToExpand = realloc(*arrayToExpand, size);

    if (!(*arrayToExpand))
    {
        fprintf(stderr, ERROR_COULD_NOT_ALLOCATE_MEMORY);
        free(oldPointer);
        exit(EXIT_FAILURE);
    }
}

static void expandIfRequired(char** word, size_t* size, int index)
{
    if (index == *size)
    {
        *size *= 2;
        expandCharArray(word, *size);
    }
}

static void readPrintableUpTo(char** word, size_t* size, char charUpTo)
{
    int readChar, index = 0;

    while ((readChar = getchar()) != EOF && isprint(readChar) && readChar != charUpTo)
    {
        expandIfRequired(word, size, index);
        (*word)[index++] = (char)readChar;
    }
    (*word)[index] = '\0';
}

static char* read(char charToSkip)
{
    char* word;
    size_t wordSize;

    wordSize = 10;
    word = malloc(wordSize);

    skipWhitespaces();
    readPrintableUpTo(&word, &wordSize, charToSkip);

    return word;
}

char* readSingleWord()
{
    /*char* cr = malloc(1000);
    scanf("%s ",cr);
    return cr;*/
    return read(' ');
}


char* readLine()
{
    /*char* line = NULL;
    size_t size;
    scanf(" ");
    getline(&line, &size, stdin);
    line[strlen(line)-1] ='\0';
    return line;*/
    return read('\n');
}

int readInt()
{
    int integer;
    scanf("%d", &integer);
    return integer;
}

/*
size_t getline(char **lineptr, size_t *n, FILE *stream) {
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL) {
        return -1;
    }
    if (stream == NULL) {
        return -1;
    }
    if (n == NULL) {
        return -1;
    }
    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);
    if (c == EOF) {
        return -1;
    }
    if (bufptr == NULL) {
        bufptr = malloc(128);
        if (bufptr == NULL) {
            return -1;
        }
        size = 128;
    }
    p = bufptr;
    while(c != EOF) {
        if ((p - bufptr) > (size - 1)) {
            size = size + 128;
            bufptr = realloc(bufptr, size);
            if (bufptr == NULL) {
                return -1;
            }
        }
        *p++ = c;
        if (c == '\n') {
            break;
        }
        c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}
*/