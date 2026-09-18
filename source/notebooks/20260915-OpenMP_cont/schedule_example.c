#include <omp.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <argp.h>

struct Args {
  size_t length;
  size_t sleep;
};

static struct argp_option options[] = {
  {"length", 'n', "size_t", 0, "Number of items to see if prime"},
  {"sleep", 's', "size_t", 0, "Number of milliseconds to sleep for if number is prime"},
};

static error_t parse_opt (int key, char *arg, struct argp_state *state)
{
  struct Args *args = state->input;
  switch (key) {
  case ARGP_KEY_INIT:
    args->length = 15;
    args->sleep = 250;
    break;
  case 'n':
    args->length = strtol(arg, NULL, 10);
    break;
  case 's':
    args->sleep = strtol(arg, NULL, 10);
    break;
  default:
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

bool isPrime(int N) {
    for (int i = 2; i < N; i++) {
        if (N % i == 0) return false;
    }
    return true;
}

int main(int argc, char **argv) {
  struct Args args;
  struct argp argp = {options, parse_opt, NULL, NULL};
  argp_parse(&argp, argc, argv, 0, 0, &args);

  #pragma omp parallel for schedule(runtime)
  for (int i = 0; i < args.length; i++) {
    int my_thread_num = omp_get_thread_num();
    bool is_prime     = isPrime(i);
    if (is_prime) usleep(args.sleep*1000);
    printf("Thread %d: %4d is %s\n", my_thread_num, i, is_prime ? "prime" : "not prime");
  }
  return 0;
}
