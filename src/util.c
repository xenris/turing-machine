#include "util.h"

char* stringCopy(char* string) {
    char* newString = malloc((strlen(string) + 1) * sizeof(char));

    if(newString == NULL) {
        puts("Failed to allocate memory for stringCopy");
        return NULL;
    }

    strcpy(newString, string);

    return newString;
}
