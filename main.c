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

int main()
{
    int processCount = 5;
    int process = 0;

    int x;
    pid_t pid;
    for (x = 1; x <= processCount; x++) {
        pid = fork();
        if (pid == 0) {
            process = x;
            break;
        }
    }
    printf("Process %d ending.\n", process);
    return 0;
    /*char filename[100];
    snprintf(filename, 99, "primes%d.txt", process)
    FILE *fp;
    fp = fopen(filename, "w");

    int i;
    for (i = 0; i < 100000000; i++) {
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
    return 0;*/
}
