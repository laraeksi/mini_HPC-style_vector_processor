#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void vector_add(float *a, float *b, float *out, int n) {
    for (int i = 0; i < n; i++) {
        out[i] = a[i] + b[i];
    }
}

float dot_product(float *a, float *b, int n) {
    float sum = 0.0f;
    for (int i = 0; i < n; i++) {
        sum += a[i] * b[i];
    }
    return sum;
}

int main(void) {
    int n = 10000000; // 10 million elements

    // Allocate three vectors on the heap
    float *a   = malloc(n * sizeof(float));
    float *b   = malloc(n * sizeof(float));
    float *out = malloc(n * sizeof(float));

    if (a == NULL || b == NULL || out == NULL) {
        fprintf(stderr, "Error: malloc failed\n");
        free(a);
        free(b);
        free(out);
        return 1; // non-zero = failure
    }

    // Seed RNG
    srand((unsigned int)time(NULL));

    // Fill a and b with random values in [0, 1)
    for (int i = 0; i < n; i++) {
        a[i] = rand() / (float)RAND_MAX;
        b[i] = rand() / (float)RAND_MAX;
    }

    // Time the vector addition
    clock_t start = clock();
    vector_add(a, b, out, n);
    clock_t end = clock();

    double seconds = (end - start) / (double)CLOCKS_PER_SEC;

    // Compute a dot product as another example operation
    float dp = dot_product(a, b, n);

    printf("Vector length: %d\n", n);
    printf("Time for vector add: %.6f seconds\n", seconds);

    double ops = (double)n;           // one add per element
    double mops = ops / 1e6 / seconds; // million ops per second

    printf("Throughput: %.2f million additions per second\n", mops);
    printf("Dot product of a.b = %.3f\n", dp);

    // Clean up
    free(a);
    free(b);
    free(out);

    return 0; // success
}
