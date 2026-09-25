#pragma once

#include <time.h>

// According to https://stackoverflow.com/a/74757391/7564988, the kernel (on Linux, hopefully with OS X and WSL too) should inject kernel code to have the time taken be insignificant

typedef double time_taken_t;
typedef struct timespec timespec_t;

inline void get_current_time(timespec_t *timespec) {
  clock_gettime(CLOCK_MONOTONIC, timespec);
}

inline double time_delta(timespec_t start, timespec_t end) {
  return ((double)(end.tv_sec - start.tv_sec)) + ((double)(end.tv_nsec - start.tv_nsec)) / 1E9;
}

inline double get_clock_resolution() {
  struct timespec timespec_res;
  clock_getres(CLOCK_MONOTONIC, &timespec_res);
  return timespec_res.tv_sec + (double)timespec_res.tv_nsec / 1E9;
}

// Below is the old timer implementation, which relies on x86 register functions
// It is not compatible with ARM based processors, so the above implementation should be good enough hopefully
// typedef unsigned long long ticks_t;
// ticks_t rdtsc() {
//   unsigned hi, lo;
//   __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
//   return ((ticks_t)lo)|( ((ticks_t)hi)<<32);
// }
