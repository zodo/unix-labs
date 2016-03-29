#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>

void run(char *command);

int main(int argc, char *argv[])
{
    //pipe 0 reading 1 writing
    run("echo hi");


    exit(EXIT_SUCCESS);
}

void run_echo()
{
    char buffer[4096];
    while (1) {
      ssize_t count = read(STDIN_FILENO, buffer, sizeof(buffer));
      if (count == -1) {
        if (errno == EINTR) {
          continue;
        } else {
          perror("read");
          exit(1);
        }
      } else if (count == 0) {
        continue;
      } else {
        write(STDOUT_FILENO, buffer, count);
      }
    }
}

void run(char* command)
{
    int fd_from_child[2];
    int fd_to_child[2];
    if (pipe(fd_from_child) == -1)
    {
      perror("pipe from child");
      exit(EXIT_FAILURE);
    }
    if (pipe(fd_to_child) == -1)
    {
      perror("pipe to child");
      exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1)
    {
      perror("fork");
      exit(1);
    }
    else if (pid == 0)
    {
      close(STDOUT_FILENO);
      close(STDIN_FILENO);
      close(fd_from_child[0]);
      close(fd_to_child[1]);
      while ((dup2(fd_from_child[1], STDOUT_FILENO) == -1) && (errno == EINTR)) {  }
      perror("stdout duplication");
      while ((dup2(fd_to_child[0], STDIN_FILENO) == -1) && (errno == EINTR)) {   }
      perror("stdin duplication");

      close(fd_from_child[1]);
      close(fd_to_child[0]);
      printf("from child");
      execl("/bin/sh", " ", NULL);
       perror("execl");
       _exit(1);
    } else {
        close(fd_from_child[1]);
        close(fd_to_child[0]);

        char buffer[4096];
        while (1) {
          pid_t pid2 = fork();
          if(pid2 != 0){
              ssize_t count = read(STDIN_FILENO, buffer, sizeof(buffer));
              if (count == -1) {
                if (errno == EINTR) {
                  continue;
                } else {
                  perror("write");
                  exit(1);
                }
              } else if (count > 0) {
                  fprintf(stderr, "%d\n", count);
                  if (strncmp(buffer, "exit\n", count) == 0){
                      kill(getppid(), 3);
                  }
                  write(fd_to_child[1], buffer, count);
            }
          }
          else{
              ssize_t count = read(fd_from_child[0], buffer, sizeof(buffer));
              if (count == -1) {
                if (errno == EINTR) {
                  continue;
                } else {
                  perror("read");
                  exit(1);
                }
              } else if (count > 0) {
                  write(STDOUT_FILENO, buffer, count);
              }
          }
        }
        close(fd_from_child[0]);
        close(fd_to_child[1]);
        wait(0);
    }
    close(fd_from_child[1]);
    close(fd_to_child[0]);
}