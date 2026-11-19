
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

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

        printf("You entered: %s", line);
    }

    free(line);

    return exit_status;
}
