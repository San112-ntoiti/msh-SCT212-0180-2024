
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>


#define MAX_ARGS 64

char **parse_line(char *line)
{
    char **args = malloc(MAX_ARGS * sizeof(char *));

    if (args == NULL)
    {
        perror("malloc");
        return NULL;
    }

    int count = 0;
    char *token = strtok(line, " \t\n");

    while (token != NULL && count < MAX_ARGS - 1)
    {
        args[count] = token;
        count++;

        token = strtok(NULL, " \t\n");
    }

    args[count] = NULL;

    return args;
}


int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t characters_read;
    int exit_status = EXIT_SUCCESS;

    while (1)
    {
        printf("msh[0]> ");
        fflush(stdout);

        characters_read = getline(&line, &capacity, stdin);

        if (characters_read == -1)
        {
            if (feof(stdin))
            {
                printf("\n");
                break;
            }

            if (ferror(stdin))
            {
                perror("getline");
                exit_status = EXIT_FAILURE;
                break;
            }
        }

       char **args = parse_line(line);

if (args == NULL)
{
    continue;
}

if (args[0] == NULL)
{
    free(args);
    continue;
}

for (int i = 0; args[i] != NULL; i++)
{
    printf("argv[%d] = %s\n", i, args[i]);
}

free(args);
    }

    free(line);

    return exit_status;
}
