#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>


#define FLOOR 100
#define CEILING 160
#define BUFFER_SIZE 16
#define LOWEST_ASCII_CODE 60
#define HIGHEST_ASCII_CODE 126
#define MAX_STRING_LENGTH 512
# define MAX_PRODUCER_THREADS 3
# define MAX_CONSUMER_THREADS 4

typedef struct Data {
    int numbers[BUFFER_SIZE];
    int currentNumber;
} Data;

void *producer (void *arg) {
    Data *data = (Data *) arg;
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        data->numbers[i] = data->currentNumber;
        data->currentNumber--;
    }
    return NULL;
}

int main (int argc, char ** argv) {
    pthread_t producerId;
    Data data = {{}, INT_MIN};
    pthread_create(&producerId, NULL, producer, (void*) &data);
    pthread_join(producerId, NULL);

    for (int i = 0; i < BUFFER_SIZE; ++i) {
        printf("%d, ", data.numbers[i]);
    }
    printf("\nx:", data.currentNumber);
    return 0;
}
