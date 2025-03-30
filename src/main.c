#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

#include "instructions.h"
#include "interpreter.h"

const size_t CELL_COUNT = 30000;

char *getFileContents(char const *const filePath);
Instruction *getInstructions(char *fileContents);

int main(int argc, char **argv)
{
    if (argc < 1)
    {
        printf("Invalid argument. Provide a file path.\n");
        exit(EXIT_FAILURE);
    }

    char const *const filePath = argv[1];
    char *fileContents = getFileContents(filePath);
    Instruction *instructions = getInstructions(fileContents);
    unsigned int instructionPointer = 0;

    uint8_t *cells = (uint8_t *)(calloc(CELL_COUNT, sizeof(uint8_t)));
    unsigned int cellPointer = 0;

    State state = {instructions, instructionPointer, cells, cellPointer};

    for (; getCurrentInstruction(&state) != HALT; ++state.instructionPointer)
    {
        switch (getCurrentInstruction(&state))
        {
        case RIGHT:
            doRight(&state);
            break;

        case LEFT:
            doLeft(&state);
            break;

        case INCREMENT:
            doIncrement(&state);
            break;

        case DECREMENT:
            doDecrement(&state);
            break;

        case OUTPUT:
            doOutput(&state);
            break;

        case INPUT:
            doInput(&state);
            break;

        case LOOP_START:
            doLoopStart(&state);
            break;

        case LOOP_END:
            doLoopEnd(&state);
            break;

        default:
            break;
        };
    }

    printf("\n");

    free(fileContents);
    free(instructions);
    exit(EXIT_SUCCESS);
}

/**
 * Returns a pointer to the contents of a file at the given path. The returned
 * pointer must be freed by the caller. Exits with `EXIT_FAILURE` upon error.
 */
char *getFileContents(char const *const filePath)
{
    FILE *file = fopen(filePath, "r");
    size_t fileSize;

    if (file == NULL)
    {
        printf("Invalid argument. File could not be opened.\n");
        exit(EXIT_FAILURE);
    }

    int status = fseek(file, 0, SEEK_END);

    if (status == -1)
    {
        printf("Failed to find end of file.\n");
        exit(EXIT_FAILURE);
    }

    const long filePosition = ftell(file);

    if (filePosition == -1)
    {
        printf("Failed to find size of file.\n");
        exit(EXIT_FAILURE);
    }

    fileSize = filePosition;
    status = fseek(file, 0, SEEK_SET);

    if (status == -1)
    {
        printf("Failed to reset file position.\n");
        exit(EXIT_FAILURE);
    }

    char *fileContents = malloc(fileSize);

    if (fileContents == NULL)
    {
        printf("Failed to allocate space for program file.\n");
        exit(EXIT_FAILURE);
    }

    const size_t itemSize = 1;
    const size_t readCount = fread(fileContents, itemSize, fileSize, file);

    if ((readCount * itemSize) != fileSize)
    {
        printf("Failed to read program file.\n");
        free(fileContents);
        exit(EXIT_FAILURE);
    }

    return fileContents;
}

/**
 * Returns a pointer to an array of instructions. This array will always end
 * with a `HALT`. The returned pointer must be freed by the caller. Exits with
 * `EXIT_FAILURE` upon error.
 */
Instruction *getInstructions(char *fileContents)
{
    int instructionIndex = 0;
    int maxInstructionCount = 128;
    Instruction *instructions = (Instruction *)(malloc(maxInstructionCount * sizeof(Instruction)));

    if (instructions == NULL)
    {
        printf("Failed to allocate space for instructions.");
        exit(EXIT_FAILURE);
    }

    for (int charIndex = 0; fileContents[charIndex] != '\0'; ++charIndex)
    {
        char nextChar = fileContents[charIndex];
        Instruction nextInstruction = charToInstruction(nextChar);

        if (nextInstruction == NOP)
        {
            continue;
        }

        instructions[instructionIndex] = nextInstruction;
        ++instructionIndex;

        if (instructionIndex == maxInstructionCount)
        {
            maxInstructionCount *= 2;
            instructions = realloc(instructions, maxInstructionCount * sizeof(Instruction));
        }
    }

    instructions[instructionIndex] = HALT;

    return instructions;
}
