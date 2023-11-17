#include <stdio.h>
#include <sys/types.h>
#include <spawn.h>
#include <sys/stat.h>
#include <sys/wait.h>


// environ variable is an array of strings like 
extern char** environ;


// GOAL CALL LS FROM THIS PROGRAM

int main(void) {
    // process id for the process
    pid_t pid;

    // path of the process we are spawning
    char *ls_path = "/usr/bin/ls";

    // arguments of the process
    char *ls_argv[2] = {"/usr/bin/ls", NULL};

    // then we put it all into posix_spawn, which gives the process a process id and spawns it!
    if (posix_spawn(&pid, ls_path, NULL, NULL, ls_argv, environ) != 0) {
        perror("Error");
    }


    // exit status variable that will be set by "waitpid".
    int exit_status;

    // waitpid returns -1 if there's an error
    if (waitpid(pid, &exit_status, 0) == -1) {
    {
        perror("waitpid");
        // Prints waitpid: The error described by errno's error code
        exit(EXIT_FAILURE);
    }

    return 0;

}
