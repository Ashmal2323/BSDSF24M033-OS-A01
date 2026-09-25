#include <stdio.h>
#include <stdlib.h>
#include "../include/mystrfunctions.h"
#include "../include/myfilefunctions.h"

int main() {
    printf("--- Testing String Functions ---\n");

    // Test mystrlen
    const char* sample = "hello";
    printf("mystrlen(\"%s\") = %d\n", sample, mystrlen(sample));

    // Test mystrcpy
    char dest1[50];
    mystrcpy(dest1, "copied text");
    printf("mystrcpy result: \"%s\"\n", dest1);

    // Test mystrncpy
    char dest2[50];
    mystrncpy(dest2, "truncated text", 5);
    printf("mystrncpy (n=5) result: \"%s\"\n", dest2);

    // Test mystrcat
    char dest3[50] = "Hello, ";
    mystrcat(dest3, "world!");
    printf("mystrcat result: \"%s\"\n", dest3);

    printf("\n--- Testing File Functions ---\n");

    // Create a small test file to work with
    FILE* writeFile = fopen("test.txt", "w");
    if (writeFile == NULL) {
        printf("Error: could not create test.txt\n");
        return 1;
    }
    fprintf(writeFile, "This is line one\n");
    fprintf(writeFile, "This is line two with apple\n");
    fprintf(writeFile, "Another line without the fruit\n");
    fprintf(writeFile, "Final line has apple again\n");
    fclose(writeFile);

    // Test wordCount
    FILE* readFile = fopen("test.txt", "r");
    if (readFile == NULL) {
        printf("Error: could not open test.txt\n");
        return 1;
    }

    int lines, words, chars;
    int wcResult = wordCount(readFile, &lines, &words, &chars);
    fclose(readFile);

    if (wcResult == 0) {
        printf("wordCount -> lines: %d, words: %d, chars: %d\n", lines, words, chars);
    } else {
        printf("wordCount failed\n");
    }

    // Test mygrep
    FILE* grepFile = fopen("test.txt", "r");
    if (grepFile == NULL) {
        printf("Error: could not open test.txt\n");
        return 1;
    }

    char** matches = NULL;
    int matchCount = mygrep(grepFile, "apple", &matches);
    fclose(grepFile);

    if (matchCount >= 0) {
        printf("mygrep found %d matching line(s) for \"apple\":\n", matchCount);
        for (int i = 0; i < matchCount; i++) {
            printf("  %s", matches[i]);  // matches[i] already ends with '\n'
        }

        // Free the memory mygrep allocated, in correct order
        for (int i = 0; i < matchCount; i++) {
            free(matches[i]);
        }
        free(matches);
    } else {
        printf("mygrep failed\n");
    }

    return 0;
}
