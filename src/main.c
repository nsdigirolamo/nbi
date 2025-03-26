#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 1)
    {
        printf("Invalid argument. Provide a file path.\n");
        exit(EXIT_FAILURE);
    }

    char const *const fileName = argv[1];
    FILE *file = fopen(fileName, "r");

    if (file == NULL)
    {
        printf("Invalid argument. File could not be opened.\n");
        exit(EXIT_FAILURE);
    }

    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    while ((read = getline(&line, &length, file)) != -1)
    {
        printf("%d %s\n", read, line);
    }

    free(line);
    exit(EXIT_SUCCESS);
}
