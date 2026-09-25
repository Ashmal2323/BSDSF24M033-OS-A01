#include "../include/myfilefunctions.h"
#include "../include/mystrfunctions.h"
#include <stdlib.h>
#include <string.h>

int wordCount(FILE* file, int* lines, int* words, int* chars) {
    if (file == NULL) {
        return -1;
    }

    *lines = 0;
    *words = 0;
    *chars = 0;

    int c;
    int inWord = 0;

    while ((c = fgetc(file)) != EOF) {
        (*chars)++;

        if (c == '\n') {
            (*lines)++;
        }

        if (c == ' ' || c == '\n' || c == '\t') {
            inWord = 0;
        } else {
            if (inWord == 0) {
                (*words)++;
                inWord = 1;
            }
        }
    }

    return 0;
}

int mygrep(FILE* fp, const char* search_str, char*** matches) {
    if (fp == NULL || search_str == NULL) {
        return -1;
    }

    int capacity = 4;
    int count = 0;
    char** result = malloc(capacity * sizeof(char*));
    if (result == NULL) {
        return -1;
    }

    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (strstr(buffer, search_str) != NULL) {
            if (count == capacity) {
                capacity *= 2;
                char** temp = realloc(result, capacity * sizeof(char*));
                if (temp == NULL) {
                    for (int i = 0; i < count; i++) {
                        free(result[i]);
                    }
                    free(result);
                    return -1;
                }
                result = temp;
            }

            int len = mystrlen(buffer);
            result[count] = malloc(len + 1);
            if (result[count] == NULL) {
                return -1;
            }
            mystrcpy(result[count], buffer);
            count++;
        }
    }

    *matches = result;
    return count;
}
