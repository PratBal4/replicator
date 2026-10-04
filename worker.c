#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

volatile sig_atomic_t stop = 0;

void handler_sigint(int) { printf("\nworker: SIGINT received\n"); }

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
    perror("\nworker: sigaction SIGINT failed\n");
    return -1;
  }
  if (sigaction(SIGTERM, &sa_term, NULL) == -1) {
    perror("\nworker: sigaction SIGTERM failed\n");
    return -1;
  }

  printf("\nworker: Executing, PID is:%d\n", getpid());

  int status;
  pid_t result;
  while (!stop) {
    sleep(1);
  }
  printf("\nworker: SIGTERM received, terminating\n");
  return 0;
}
