#include "main.h"

int main(int argc, char** args) {
    if(argc != 2) {
        printHelp();
        return -1;
    }

    const char* filePath = args[1];

    bool printSubSteps = false;

    FILE* file = fopen(filePath, "r");

    if(file == NULL) {
        printf("Error opening file %s\n", filePath);
        return -1;
    }

    Machine* machine = machineCreate(file);

    fclose(file);

    if(machine == NULL) {
        printf("Error creating machine from file %s\n", filePath);
        return -1;
    }


    const int lineLength = 512;
    char line[lineLength];
    fgets(line, lineLength, stdin);
    line[strlen(line) - 1] = '\0';
    machineSetTape(machine, tapeCreate(line, machine->blank));
    machineReset(machine);

    putchar('\n');
    tapePrint(machine->tape);
    putchar('\n');

    bool done = false;
    while(!done) {
        if(printSubSteps) {
            printf("%s\n", machine->state);
            tapePrint(machine->tape);
        }

        if(!machineStep(machine)) {
            done = true;
        }

        if(printSubSteps) {
            printf("\n");
            usleep(1000000 / 4);
        }
    }

    tapePrint(machine->tape);

    machineDelete(machine);

    return 0;
}

void printHelp() {
    puts("help");
}
