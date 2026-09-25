#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc > 3 || argc < 1) {
    fprintf(stderr, "Usage: %s N [p]\n", argv[0]);
    return 1;
  }
  long N = atol(argv[1]);
  long fibs[N];
  double time = omp_get_wtime();
  fibs[0] = 1;
  fibs[1] = 2;
  for (long i=2; i<N; i++)
    fibs[i] = fibs[i-1] + fibs[i-2];
  if (argc == 3 && argv[2][0] == 'p') {
    for (long i=0; i<N; i++)
      printf("%2ld: %5ld\n", i+1, fibs[i]);
  }
  printf("Time taken: %g\n", omp_get_wtime() - time);
  return 0;
}
