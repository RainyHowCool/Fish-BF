#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMSIZE 4096
#define BYTE unsigned char

#define bool int
#define true 1
#define false 0

BYTE* mem;

void bfExec(char* code) {
    char buffer[MEMSIZE] = {'\0'};
    int index = 0;

    bool ignore = false;
    bool begin_loop = false;

    for (int i = 0; i < strlen(code); i++){
        char chr = code[i];

        if (ignore) {
            if(chr == ']') ignore = false;
            continue;
        } else if (begin_loop) {
            if(chr == ']') begin_loop = false;
            else buffer[index++] = chr;
        }

        switch (chr) {
        case '+':
            if (*mem <= 255) (*mem)++;
            break;
        case '-':
            if (*mem >= 0) (*mem)--;
            break;
        case '>':
            if (++mem == NULL) mem--;
            break;
        case '<':
            if (--mem == NULL) mem++;
            break;
        case '[':
            if (*mem == 0) ignore = true;
            else begin_loop = true;
            break;
        case ']':
            while (*mem) bfExec(buffer);
            break;
        case '.':
            putchar(*mem);
            break;
        case ',':
            *mem = getchar();
            break;
        }
    }
    
    return;
}

int main(int argc, char* argv[]) { /* Main */
    puts("Fish-BF ver Alpha 1.00");
    puts("2025 xiaokuai ");

    char* input = malloc(MEMSIZE);

    mem = (BYTE*) calloc(MEMSIZE, MEMSIZE);

    if(argc > 1){
        for (int i = 1; i < argc; i++) {
            FILE* fp = fopen(argv[i], "r");

            if (fp == NULL) {
                fprintf(stderr, "Cannot open file \"%s\"!", argv[i]);
                continue;
            }

            while (fgets(input, MEMSIZE, fp) != NULL) bfExec(input);

            continue;
        }
    }

    while(true){
        memset(mem, 0, MEMSIZE);

        printf("\n><FISH-^> ");

        if(fgets(input, MEMSIZE, stdin) != NULL) {
            bfExec(input);
        }

        strcpy(input, "");
    }

    return 0;
}
