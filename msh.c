
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

#include <unistd.h> //the 3 will provide process creation execution waiting and error handling
#include <sys/wait.h>
#include <errno.h>


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

//external command execution function
int execute_external(char **args)
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        execvp(args[0], args);
        perror(args[0]);
        _exit(127);
    }

    int status;
    pid_t result;

    do
    {
        result = waitpid(pid, &status, 0);
    }
    while (result == -1 && errno == EINTR);

    if (result == -1)
    {
        perror("waitpid");
        return 1;
    }

    if (WIFEXITED(status))
    {
        return WEXITSTATUS(status);
    }

    if (WIFSIGNALED(status))
    {
        return 128 + WTERMSIG(status);
    }

    return 1;
}


//built in handler

int handle_builtin(char **args, int *should_exit)
{
    if (strcmp(args[0], "cd") == 0)
    {
        const char *directory = args[1];

        if (directory == NULL)
        {
            directory = getenv("HOME");
        }

        if (directory == NULL)
        {
            fprintf(stderr, "msh: HOME is not set\n");
            return 1;
        }

        if (chdir(directory) == -1)
        {
            perror("cd");
            return 1;
        }

        return 0;
    }
    else if (strcmp(args[0], "help") == 0)
    {
        printf("msh - Minimal Unix Shell\n");
        printf("Built-in commands:\n");
        printf("  cd [dir]  Change directory\n");
        printf("  help      Display help\n");
        printf("  exit      Exit the shell\n");

        return 0;
    }
    else if (strcmp(args[0], "exit") == 0)
    {
        *should_exit = 1;
        return 0;
    }

    return 1;
}



int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t characters_read;
    int exit_status = EXIT_SUCCESS;
    int should_exit = 0;
    int last_status = 0;

    while (1)
    {
        printf("msh[%d]> ", last_status);
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

if (strcmp(args[0], "cd") == 0 ||
    strcmp(args[0], "help") == 0 ||
    strcmp(args[0], "exit") == 0)
{
    last_status = handle_builtin(args, &should_exit);
}
else
{
    last_status = execute_external(args);
}

free(args);

if (should_exit)
{
    break;
}
    }

    free(line);

    return exit_status;
}
