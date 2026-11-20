NEWTON MWIRIGI NTOITI
SCT212-0180/2024
ICS2305 SYSTEMS PROGRAMMING

msh= Minimal Unix Shell

description:
A small implementation of a Unix shell written in C. This project illustrates OS concepts such as: Forking processes, executing commands, process synchronisation, managing signals, and file descriptors.

Building and Running
Requirements: GCC and a POSIX-compatible Linux environment.
compile:  gcc -Wall -Wextra -Werror -std=c11 msh.c -o msh
run: ./msh
Exit using the exit command or Ctrl+D.

what i implemented:
Shell prompt and input using getline()
Command parsing using strtok()
External command execution using fork() and execvp()
Built-in commands: cd, help, exit
Previous command exit status
Background execution and zombie prevention
Output redirection using open() and dup2()
Ctrl+C signal handling

the design:
The shell repeatedly displays a prompt containing the exit status of the previous command and reads user input using getline(). This allows complete input lines to be accepted dynamically. The input is tokenized using strtok(), with spaces and tabs used as delimiters. The resulting argument array is NULL-terminated for compatibility with command execution functions.

External commands are executed using process creation. The shell calls fork() to create a child process, and the child uses execvp() to replace itself with the requested program. The parent uses waitpid() to wait for foreground commands and determine their exit status. Exit codes are obtained using WIFEXITED() and WEXITSTATUS(), while terminated processes use WIFSIGNALED() and the signal number.

The cd and exit commands must be built-ins because they need to affect the shell process itself. If cd ran in a child process, only the child's working directory would change. Similarly, executing exit in a child would not terminate the parent shell. The help command is also implemented internally.

Background commands are started without blocking the parent shell. The shell periodically uses waitpid() with WNOHANG to collect completed background children and prevent zombie processes.

Output redirection uses open() to create or truncate files and dup2() to redirect standard output. Signal handling allows the shell to ignore Ctrl+C while child processes restore the default SIGINT behaviour.



encountered limitations include:
Maximum of 63 command arguments.
No command history, pipes, or append redirection (>>).
No advanced quoting or environment-variable expansion.
Only basic output redirection is supported.
No full interactive job-control implementation.

sources:
Linux manual pages: fork(2), execvp(3), waitpid(2), getline(3), chdir(2), open(2), dup2(2), and sigaction(2).
POSIX system programming documentation.
i also used gpt as a learning assistant and honestly sam altman is doing a good job.