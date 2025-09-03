#include <stdlib.h>
#include <stdio.h>

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

    return 0;
}
