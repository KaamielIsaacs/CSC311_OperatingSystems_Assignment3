#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

float global_value = 64.0;  // shared variable set to 64.0
pthread_mutex_t lock_guard;  // mutex named  lock_guard  

// function to increment shared variable 
void* increment(void* arg) {
    pthread_mutex_lock(&lock_guard); // lock access
    global_value += 1.0; // increment global value
    printf("Incremented shared variable: %.2f\n", global_value);
    pthread_mutex_unlock(&lock_guard); // unlock access
    return NULL;
}

// function to decrement shared variable
void* decrement(void* arg) {
    pthread_mutex_lock(&lock_guard);
    global_value -= 1.0; //decrementing the value
    printf("Decremented shared variable: %.2f\n", global_value);
    pthread_mutex_unlock(&lock_guard);
    return NULL;
}

// function to double the shared variable
void* multiply_by_two(void* arg) {
    pthread_mutex_lock(&lock_guard);
    global_value *= 2.0;
    printf("Doubled shared variable: %.2f\n", global_value);
    pthread_mutex_unlock(&lock_guard);
    return NULL;
}

// function to divide shared variable by 2
void* divide_by_two(void* arg) {
    pthread_mutex_lock(&lock_guard);
    global_value /= 2.0; //divide the shared variable by 2
    printf("Halved shared variable: %.2f\n", global_value);
    pthread_mutex_unlock(&lock_guard);
    return NULL;
}

int main() {
    pthread_t thread1, thread2, thread3, thread4;

    if (pthread_mutex_init(&lock_guard, NULL) != 0) { //initialize the mutex 
        printf("Mutex initialization failed\n");
        return 1;
    }

    printf("Initial float variable: %.2f\n", global_value);

    // create threads for different operations on shared variable
    pthread_create(&thread1, NULL, increment, NULL);
    pthread_create(&thread2, NULL, decrement, NULL);
    pthread_create(&thread3, NULL, multiply_by_two, NULL);
    pthread_create(&thread4, NULL, divide_by_two, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);

    printf("Final value: %.2f\n", global_value);
    pthread_mutex_destroy(&lock_guard);

    return 0;
}