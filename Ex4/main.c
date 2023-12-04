#include <stdio.h>
#include <pthread.h>

unsigned long long calculate_catalan(int n) {
    if (n <= 1) {
        return 1;
    }
    unsigned long long result = 0;
    for (int i = 0; i < n; i++) {
        result += calculate_catalan(i) * calculate_catalan(n - i - 1);
    }
    return result;
}

int is_prime(int number) {
    if (number <= 1) {
        return 0;
    }
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0) {
            return 0;
        }
    }
    return 1;
}

struct ChildThreadArgs {
    int n;
    unsigned long long catalan_result;
    int prime_count;
};

void *thread_function(void *arg) {
    struct ChildThreadArgs *args = (struct ChildThreadArgs *)arg;
    for (int i = 0; i <= args->n; i++) {
        args->catalan_result = calculate_catalan(i);
        printf("Thread: Calculated Catalan Number for N = %d: %llu\n", i, args->catalan_result);
        args->prime_count = 0;  // Reset prime count for each Catalan number
        for (int j = 2; j <= args->catalan_result; j++) {
            if (is_prime(j)) {
                args->prime_count++;
            }
        }
        printf("Thread: Count of Prime Numbers for N = %d: %d\n", i, args->prime_count);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    struct ChildThreadArgs args;
    printf("Enter the number 'N' of Catalan Numbers to calculate: ");
    scanf("%d", &args.n);
    pthread_create(&thread, NULL, thread_function, &args);
    pthread_join(thread, NULL);
    printf("Last calculated Catalan Number: %llu\n", args.catalan_result);
    printf("Count of Prime Numbers up to last calculated Catalan Number: %d\n", args.prime_count);
    return 0;
}
