#include <stdio.h>
#include <unistd.h>
int main() {
  int x = 1;
  #pragma omp parallel
  #pragma omp single
  {
    #pragma omp task shared(x) depend(out: x)
    {
      usleep(1);
      x = 2;
    }
    #pragma omp task shared(x) depend(in: x)
    printf("x + 1 = %d. ", x+1);
    #pragma omp task shared(x) depend(in: x)
    printf("x + 2 = %d. ", x+2);
  }
  puts("");
  return 0;
}
