#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "No input file given.\n");
        return 1;
    }

    FILE* fptr;
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        fprintf(stderr, "File or directory '%s' not found.\n", argv[1]);
        return 1;
    }
    int tokenCount = 0;
    int capacity = 1;
    char** tokens = (char**)malloc(capacity * sizeof(char*));
    char tmp[64] = "";
    while (TRUE) {
        char current = fgetc(fptr);
        if (isspace(current)) continue;
        else if (isalpha(current)) {
            char str[2] = "";
            str[0] = current;
            str[1] = '\0';
            strcat(tmp, str);
            
            char next = fgetc(fptr);
            for (; isalnum(next); current = next, next = fgetc(fptr)) {
                char str[2] = "";
                str[0] = next;
                str[1] = '\0';
                strcat(tmp, str);
            }
            ungetc(next, fptr);
            if (tokenCount >= capacity) {
                capacity *= 2;
                char** tempTokens = realloc(tokens, capacity * sizeof(char*));
                tokens = tempTokens;
            }
            tokens[tokenCount] = malloc(strlen(tmp) * sizeof(char) + 1);
            strcpy(tokens[tokenCount], tmp);
            strcpy(tmp, "");
            tokenCount++;
            continue;
        }
        break;
    }
    for (int i = 0; i < tokenCount; i++) {
        free(tokens[i]);
    }
    free(tokens);
    return 0;
}
