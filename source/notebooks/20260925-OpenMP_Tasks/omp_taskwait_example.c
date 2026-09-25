#include <omp.h>
#include <stdio.h>
#include <unistd.h>
void bar(int i, int time, char task);
void foo(int i);

int main() {
  #pragma omp parallel
  #pragma omp single nowait
  {
    for (int i = 0; i < 4; i++) {
      // Create tasks with foo and their own custom `i` value
      #pragma omp task firstprivate(i)
      foo(i);
    }
  }
  return 0;
}

void foo(int i) {
  // Foo then creates two child tasks with different parameters
  #pragma omp task shared(i)
  bar(i, 1000, 'a');

  #pragma omp task shared(i)
  bar(i, 0, 'b');

  #pragma omp taskwait // Wait until child bar tasks are done before proceeding
  int id = omp_get_thread_num();
  printf("task %d\tfinish\tid: %d\n", i, id);
}

void bar(int i, int time, char task) {
  int id = omp_get_thread_num();
  usleep(time); // Make some tasks take longer
  printf("task %d.%c\tid: %d\n", i, task, id);
}

