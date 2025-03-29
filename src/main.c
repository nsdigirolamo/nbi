#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

#include "instructions.h"

const size_t CELL_COUNT = 30000;

char *getFileContents(char const *const filePath);

int main(int argc, char **argv)
{
    if (argc < 1)
    {
        printf("Invalid argument. Provide a file path.\n");
        exit(EXIT_FAILURE);
    }

    char const *const filePath = argv[1];
    char *fileContents = getFileContents(filePath);

    for (int i = 0; fileContents[i] != '\0'; ++i)
    {
        char nextChar = fileContents[i];
        Instruction nextInstruction = getNextInstruction(nextChar);
        if (nextInstruction != NOP)
        {
            printf("%s ", InstructionToString(nextInstruction));
        }
        printf("\n");
    }

    free(fileContents);
    exit(EXIT_SUCCESS);
}

/**
 * Returns the contents of a file at the given path. Exits with `EXIT_FAILURE`
 * upon error.
 */
char *getFileContents(char const *const filePath)
{
    FILE *file = fopen(filePath, "r");
    long fileSize;

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

    fileSize = ftell(file);

    if (fileSize == -1)
    {
        printf("Failed to find size of file.\n");
        exit(EXIT_FAILURE);
    }

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

    size_t readCount = fread(fileContents, 1, fileSize, file);

    if ((long)(readCount) != fileSize)
    {
        printf("Failed to read program file.\n");
        free(fileContents);
        exit(EXIT_FAILURE);
    }

    return fileContents;
}
