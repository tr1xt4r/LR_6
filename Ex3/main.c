#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int num_iterations;
int min_random_number;
int max_random_number;
int target_random_number;
int exit_condition = 0;

struct ChildThreadArgs {
    char *name;
    char *message;
};

void *child_thread_function(void *arg) {
    struct ChildThreadArgs *args = (struct ChildThreadArgs *)arg;
    for (int i = 1; i <= num_iterations; i++) {
        if (exit_condition) {
            printf("Child Thread %s. Exiting due to exit condition.\n", args->name);
            pthread_exit(NULL);
        }
        printf("Child Thread %s. %s %d\n", args->name, args->message, i);
        int random_number = min_random_number + rand() % (max_random_number - min_random_number + 1);
        printf("Child Thread %s. Random Number: %d\n", args->name, random_number);
        if (random_number == target_random_number) {
            printf("Child Thread %s. Received %d, setting exit condition.\n", args->name, target_random_number);
            exit_condition = 1;
        }
        sleep(1);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t child_threads[2];
    struct ChildThreadArgs args[] = {
            {"1", "Message1"},
            {"2", "Message2"}
    };
    printf("Enter the number of iterations: ");
    scanf("%d", &num_iterations);
    printf("Enter the minimum random number: ");
    scanf("%d", &min_random_number);
    printf("Enter the maximum random number: ");
    scanf("%d", &max_random_number);
    printf("Enter the target random number: ");
    scanf("%d", &target_random_number);
    srand(time(NULL));
    for (int i = 0; i < 2; i++) {
        if (pthread_create(&child_threads[i], NULL, child_thread_function, &args[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }
    for (int i = 0; i < 2; i++) {
        if (pthread_join(child_threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
    }
    printf("Main Thread. All child threads have completed.\n");
    return 0;
}
