#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 256
#define MAX_PASSWORD 10

#define SUCCESS "Password verified\n"
#define INVALID "Invalid password\n"
#define NO_USER "No such user\n"

int main(void) {
    char user_id[MAXLINE];
    char password[MAXLINE];
    int file_descriptor[2], status;
    pid_t pid;
    int piped = pipe(file_descriptor);

    if(fgets(user_id, MAXLINE, stdin) == NULL) {
        perror("fgets");
        exit(1);
    }

    if(fgets(password, MAXLINE, stdin) == NULL) {
        perror("fgets");
        exit(1);
    }

    if(piped == -1){
        perror("pipe");
        exit(1);
    }

    pid = fork();

    if(pid == 0){
        close(file_descriptor[1]);
        if(dup2(file_descriptor[0], 0) == -1){
            perror("dup2");
            exit(1);
        }
        close(file_descriptor[0]);
        execl("./validate", "validate", NULL);
        perror("execl");
        exit(126);
    }

    else if(pid > 0){
        close(file_descriptor[0]);
        if(write(file_descriptor[1], user_id, MAX_PASSWORD) == -1){
            perror("write");
            exit(1);
        }
        if(write(file_descriptor[1], password, MAX_PASSWORD)== -1){
            perror("write");
            exit(1);
        }
        close(file_descriptor[1]);
        if(wait(&status) == -1){
            perror("wait");
            exit(1);
        }
        else{
            if (WIFEXITED(status)){
                switch(WEXITSTATUS(status)){
                    case 0:
                        printf(SUCCESS); break;
                    case 2:
                        printf(INVALID); break;
                    case 3:
                        printf(NO_USER); break;
                    default:
                        printf("Error has occured. \n");
                        exit(1);
                }
            }
            else {
              perror("status");
              exit(1);
            }
        }
    }

    else{
        perror("fork");
        exit(1);
    }

    return 0;
}
