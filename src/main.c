#include "main.h"

int main(int argc, char** args) {
    char* filePath = NULL;

    bool printSubSteps = false;
    int delayMillis = 0;
    char* tapeData = NULL;

    int opt;
    while((opt = getopt(argc, args, "s:d:t:")) != -1) {
        switch(opt) {
        case 's':
            filePath = optarg;
            break;
        case 'd':
            delayMillis = atoi(optarg);
            printSubSteps = true;
            break;
        case 't':
            tapeData = optarg;
            break;
        default:
            return -1;
        }
    }

    if(filePath == NULL) {
        printHelp();
        return -1;
    }

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

    Tape* tape = NULL;

    if(tapeData == NULL) {
        const int lineLength = 512;
        char line[lineLength];

        while(fgets(line, lineLength, stdin) != NULL) {
            line[strlen(line) - 1] = '\0';

            tape = tapeCreate(line, machine->blank);

            machineReset(machine);

            while(machineStep(machine, tape));

            tapePrint(tape, false, 0);

            tapeDelete(tape);
        }
    } else {
        tape = tapeCreate(tapeData, machine->blank);

        machineReset(machine);

        const int maxLabelLength = programGetMaxStateLabelLength(machine->program);

        bool done = false;
        while(!done) {
            if(printSubSteps) {
                const int trailingSpaceCount = maxLabelLength + 1 - strlen(machine->state);
                printf("%s%*c", machine->state, trailingSpaceCount, ' ');
                tapePrint(tape, true, maxLabelLength + 1);
            }

            if(!machineStep(machine, tape)) {
                done = true;
            }

            if(printSubSteps) {
                printf("\n");
                usleep(delayMillis * 1000);
            }
        }

        if(!printSubSteps) {
            tapePrint(tape, false, 0);
        }

        tapeDelete(tape);
    }

    machineDelete(machine);

    return 0;
}

void printHelp() {
    puts("Help:");
    puts("");
    puts("    turing [options]");
    puts("");
    puts("    -s [path]");
    puts("        Specifies the source file to use.");
    puts("");
    puts("    -d [millis]");
    puts("        If set the tape will be printed for each step of the machine with \"millis\" delay between each. (Ignored when getting input from stdin.)");
    puts("");
    puts("    -t [tape]");
    puts("        Sets the initial value of the tape. If not set the inital tape value will be read in through stdin.");
    puts("");
    puts("    e.g. \"turing -s example.tu -d 500 -t 001010\"");
    puts("         \"cat input.txt | turing -s example.tu > output.txt\"");
}
