#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

unsigned long long *factor(unsigned long long composite)
{
    unsigned long long end = composite;
    unsigned long long *factors = malloc(10000 * sizeof(unsigned long long));
    int factorIndex = 0;
    unsigned long long i;
    for (i = 2; i <= end; i++) {
        if (composite % i == 0) {
            composite /= i;
            factors[factorIndex++] = i;
            i = 2;
            if (composite < 2) {
                break;
            }
        }
    }
    int x;
    for (x = factorIndex; x < 10000; x++) {
        factors[x] = 0;
    }
    return factors;
}

int main(int argc, char *argv[])
{
    int processCount = 8;
    int process = 0;
    int highestToFactor = 1000000;

    int x;
    pid_t pid;
    for (x = 1; x < processCount; x++) {
        pid = fork();
        if (pid == 0) {
            process = x;
            break;
        }
    }

    int eachProcessToFactor = highestToFactor / processCount,
        processIntervalMin = eachProcessToFactor * process,
        processIntervalMax = processIntervalMin + eachProcessToFactor;

    char filename[100];
    snprintf(filename, 99, "primes-%d-%d.txt", processIntervalMin, processIntervalMax);
    FILE *fp;
    fp = fopen(filename, "w");

    int i;
    for (i = processIntervalMin; i < processIntervalMax; i++) {
        fprintf(fp, "%d - ", i);
        long long *factors = factor(i);
        int x;
        for (x = 0; x < 10000; x++) {
            if (factors[x] != 0) {
                fprintf(fp, "%d ", factors[x]);
            }
        }
        free(factors);
        fprintf(fp, "\n");
    }

    fclose(fp);
    return 0;
}
