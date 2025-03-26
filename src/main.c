#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef enum
{
    RIGHT,
    LEFT,
    INCREMENT,
    DECREMENT,
    OUTPUT,
    INPUT,
    LOOP_START,
    LOOP_END,
    NOP,
} Instruction;

Instruction getNextInstruction(char symbol);

int main(int argc, char **argv)
{
    if (argc < 1)
    {
        printf("Invalid argument. Provide a file path.\n");
        exit(EXIT_FAILURE);
    }

    char const *const fileName = argv[1];
    FILE *file = fopen(fileName, "r");
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

    if (readCount != fileSize)
    {
        printf("Failed to read program file.\n");
        free(fileContents);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; fileContents[i] != '\0'; ++i)
    {
        char nextChar = fileContents[i];
        Instruction nextInstruction = getNextInstruction(nextChar);
        if (nextInstruction != NOP)
        {
            printf("%d ", nextInstruction);
        }
        printf("\n");
    }

    free(fileContents);
    exit(EXIT_SUCCESS);
}

Instruction getNextInstruction(char symbol)
{
    switch (symbol)
    {
    case '>':
        return RIGHT;
    case '<':
        return LEFT;
    case '+':
        return INCREMENT;
    case '-':
        return DECREMENT;
    case '.':
        return OUTPUT;
    case ',':
        return INPUT;
    case '[':
        return LOOP_START;
    case ']':
        return LOOP_END;
    default:
        return NOP;
    }
}
