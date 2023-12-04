#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *child_thread_function(void *arg) {
    int i;
    for (i = 1; i <= 10; i++) {
        printf("Child Thread. Iteration: %d\n\n", i);
        sleep(2);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t child_thread;
    int i;
    if (pthread_create(&child_thread, NULL, child_thread_function, NULL) != 0) {
        perror("pthread_create");
        exit(1);
    }
    for (i = 1; i <= 10; i++) {
        printf("Main Thread. Iteration: %d\n\n", i);
        sleep(2);
    }
    if (pthread_join(child_thread, NULL) != 0) {
        perror("pthread_join");
        exit(1);
    }
    return 0;
}
