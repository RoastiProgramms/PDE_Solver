#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define D 100
#define T 1
#define M 10000000
#define NUM_THREADS 4

double g(double x[], int d) {
    double norm_sq = 0;
    for (int i = 0; i < d; i++) {
        norm_sq += x[i] * x[i];
    }
    return log((1 + norm_sq) / 2);
}

int main() {
    srand(time(NULL));
    double t = 0;
    double* dW = (double*)malloc(sizeof(double) * D * M);
    double MC = 0;
    double start = omp_get_wtime();

    for (int m = 0; m < M; m++) {
        for (int i = 0; i < D; i++) {
            dW[m * D + i] = rand() / (double)RAND_MAX;
        }
    }
#pragma omp parallel for reduction(+:MC) num_threads(NUM_THREADS)
    for (int m = 0; m < M; m++)
        double norm_sq = 0;
    for (int i = 0; i < D; i++) {
        double val = dW[m * D + i];
        norm_sq += val * val;
    }
    double g_val = log((1 + norm_sq) / 2);
    MC += exp(-g_val);
}
MC = -log(MC / M);
double end = omp_get_wtime();
double time_elapsed = end - start;
printf("Solution: u(T,0) = %f;\n", g(NULL, 0));
printf("Solution: u(0,0) = %f;\n", MC);
printf("Time = %f;\n", time_elapsed);
free(dW);
return 0;
}







