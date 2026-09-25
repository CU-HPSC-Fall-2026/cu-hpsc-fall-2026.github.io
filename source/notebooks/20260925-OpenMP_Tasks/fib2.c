#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

long fib(long n) {
  if (n < 2) return n;
  long n1, n2;
  #pragma omp task shared(n1)
  n1 = fib(n - 1);
  #pragma omp task shared(n2)
  n2 = fib(n - 2);
  #pragma omp taskwait
  return n1 + n2;
}

int main(int argc, char **argv) {
  if (argc > 3 || argc < 1) {
    fprintf(stderr, "Usage: %s N [p]\n", argv[0]);
    return 1;
  }
  long N = atol(argv[1]);
  long fibs[N];
  double time = omp_get_wtime();
  #pragma omp parallel
  #pragma omp single nowait
  {
    for (long i=0; i<N; i++)
      fibs[i] = fib(i+1);
  }
  if (argc == 3 && argv[2][0] == 'p') {
    for (long i=0; i<N; i++)
      printf("%2ld: %5ld\n", i+1, fibs[i]);
  }
  printf("Time taken: %g\n", omp_get_wtime() - time);
  return 0;
}
