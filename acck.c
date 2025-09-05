#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1

struct Token {
    char* tokenName;
    char* value;
};

struct Tokens {
    int tokenCount;
    int capacity;
    char** tokenStrings;
};

void appendToken(struct Tokens* tokens, char* token) {
    if (tokens->tokenCount >= tokens->capacity) {
                tokens->capacity *= 2;
                char** tempTokenStrings = realloc(tokens->tokenStrings, tokens->capacity * sizeof(char*));
                tokens->tokenStrings = tempTokenStrings;
    }
    tokens->tokenStrings[tokens->tokenCount] = malloc(strlen(token) * sizeof(char) + 1);
    strcpy(tokens->tokenStrings[tokens->tokenCount], token);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "No input file given.\n");
        return 1;
    }
    struct Tokens tokens = {0, 1, NULL};
    FILE* fptr;
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        fprintf(stderr, "File or directory '%s' not found.\n", argv[1]);
        return 1;
    }
    tokens.tokenStrings = (char**)malloc(tokens.capacity * sizeof(char*));
    char tmp[64] = "";
    while (TRUE) {
        char current = fgetc(fptr);
        if (isspace(current)) continue;
        else if (isalpha(current)) {
            tmp[strlen(tmp)] = current;     // Append character to token buffer
            for (current = fgetc(fptr); isalnum(current); current = fgetc(fptr)) {     // Peek at next character until it is not a valid part of a keyword or identifier
                tmp[strlen(tmp)] = current;
            }
            ungetc(current, fptr);     // Put back last consumed character into input stream
            appendToken(&tokens, tmp); 
            memset(tmp, 0, strlen(tmp));    // Clear token buffer for next iteration
            tokens.tokenCount++;
            continue;
        }
        break;
    }
    for (int i = 0; i < tokens.tokenCount; i++) {
        free(tokens.tokenStrings[i]);
    }
    free(tokens.tokenStrings);
    return 0;
}
