#include <stdio.h>

void printArgv(char* argv[], int argvAmount) {
    if(argvAmount) {
        printf("\n%s", argv[argvAmount]);
        printArgv(argv, argvAmount - 1);
    }
}

void saveArgvToFile(FILE* f, char* argv[], int argvAmount) {
    if(argvAmount) {
        fprintf(f, "%s\n", argv[argvAmount]);
        saveArgvToFile(f, argv,argvAmount - 1);
    }
}

int printStartNumberProgram() {
    int i = -1;
    FILE* f = fopen("startsAmount.txt", "r");
    if(f != NULL) {
        fscanf(f,"%d", &i);
        if(i == -1) {
            i = 0;
        }
    } else {
        i = 0;
    }
    printf("Program start number: %d", i);
    fclose(f);
    return i;
}

void setNumberForNext(int i) {
    FILE* f = fopen("startsAmount.txt", "w");
    if(f != NULL) {
        fprintf(f,"%d", i);
    }
    fclose(f);
}

/*
recursion
files
*/

void main(int argc, char* argv[]) {
    setNumberForNext(printStartNumberProgram() + 1);
    printArgv(argv, argc - 1);
    FILE* f = fopen("test.txt", "w");
    if(f != NULL) {    
        saveArgvToFile(f, argv, argc - 1);
    }else {
        printf("ERROR, can not open test.txt for reading");
    }
    fclose(f);
}