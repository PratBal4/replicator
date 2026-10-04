#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

volatile sig_atomic_t stop = 0;

void handler_sigint(int) { printf("\nsupervisor: SIGINT received\n"); }

void handler_sigterm(int) { stop = 1; }

int main() {
  struct sigaction sa_int;
  struct sigaction sa_term;

  sa_int.sa_handler = handler_sigint;
  sa_term.sa_handler = handler_sigterm;

  sigemptyset(&sa_int.sa_mask);
  sigemptyset(&sa_term.sa_mask);

  sa_int.sa_flags = 0;
  sa_term.sa_flags = 0;

  if (sigaction(SIGINT, &sa_int, NULL) == -1) {
    perror("\nsupervisor: sigaction SIGINT failed\n");
    return -1;
  }
  if (sigaction(SIGTERM, &sa_term, NULL) == -1) {
    perror("\nsupervisor: sigaction SIGTERM failed\n");
    return -1;
  }

  pid_t pid = fork();

  if (pid == -1) {
    perror("\nsupervisor: fork failed\n");
    return -2;
  }

  if (pid == 0) {
    printf("\nsupervisor: Supervisor running with PID:%d\n", getppid());
    execl("./worker", "worker", NULL);
    perror("\nsupervisor: execl failed\n");
    return -2;
  }

  else {
    int status;
    pid_t result;
    while (!stop) {
      result = waitpid(pid, &status, 0);
      if (result == -1) {
        if (errno == EINTR) {
          continue;
        }
        perror("\nsupervisor: waitpid failed\n");
        return -3;
      }
      if (result == pid) {
        if (WIFEXITED(status)) {
          printf("\nsupervisor: Worker terminated normally with exit code:%d\n",
                 WEXITSTATUS(status));
        }
        if (WIFSIGNALED(status)) {
          printf("\nsupervisor: Worker terminated via signal of code:%d\n",
                 WTERMSIG(status));
        }
        pid_t pid_new = fork();
        if (pid_new == -1) {
          perror("\nsupervisor: New fork failed\n");
          return -2;
        }
        if (pid_new == 0) {
          printf("\nsupervisor: New process created\n");
          execl("./worker", "worker", NULL);
          perror("\nsupervisor: New execl failed\n");
          return -2;
        } else {
          pid = pid_new;
        }
      }
      sleep(1);
    }
    printf("\nsupervisor: Termination received, exiting\n");
    int kill_result = kill(pid, SIGTERM);
    if (kill_result == -1) {
      printf("\nsupervisor: kill failed\n");
      return -4;
    }
  }
  return 0;
}
