void triad(int N, double *restrict a, const double *restrict b, double scalar, const double *restrict c) {
    for (int i=0; i<N; i++)
        a[i] = b[i] + scalar * c[i];
}

void foo(double *x) {
    triad(2, x, x, 10, x);
}

void foo_harder(double *x) {
  triad(2, x+1, x, 10, x);
}

