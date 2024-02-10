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

typedef struct ThreadArg {
    char letters[BUFFER_SIZE];
    int numbers[BUFFER_SIZE];
} ThreadArg;

typedef struct ResultSet {
    ThreadArg *input;
    int results[BUFFER_SIZE];
    int resultCount;
} ResultSet;

//
//char string[255] = {0};
//
///*do something*/
//strcpy( string, "[" );
//for( size_t i = 0; i < (sizeof(array)/sizeof(int)) -1; i++ )
//{
//sprintf( &string[ strlen(string) ],  "%d, ", array[i] );
//}
//
//sprintf( &string[ strlen(string) ],  "%d", array[4] );

char * intArrayToString (int intArray[], size_t intArraySize) { //}, char destination [], size_t stringLength) {
    char string[] = "";
    for (int i = 0; i < intArraySize; ++i) {
        char buf[4];
        int n = sprintf( buf, "%d", intArray[i]);
        strcat(buf, ", ");
//        strcat(string, buf);
        printf("%s", buf);
//        printf("%d\n", intArray[i]);
//        snprintf(&string, size,"%d", array[i]);
//        printf("current:%s", string);
    }
    printf("\n");
//    return string;
}

void randomizeIntArray (int array[], size_t size) {
    for (int i = 0; i < size; ++i) {
        array[i] = (int) (rand() % (CEILING - FLOOR + 1) + FLOOR);
//        printf("array[%d]=%d\n", i, array[i]);
    }
}

void randomizeCharArray (char array[], size_t size) {
    for (int i = 0; i < size; ++i) {
        int offset = (rand() % (HIGHEST_ASCII_CODE - LOWEST_ASCII_CODE + 1)
                + LOWEST_ASCII_CODE);
        array[i] = rand() % (HIGHEST_ASCII_CODE - LOWEST_ASCII_CODE + 1) + LOWEST_ASCII_CODE;
//        printf("array[%d]=%c\n", i, array[i]);
    }
}

void removeEvens (int array[BUFFER_SIZE]) {
    for (int i = 0; i < BUFFER_SIZE -1 ; ++i) {
        if (array[i] % 2 == 0 && array[i+1] %2 != 0) {
            array[i] = array[i+1];
        }
    }
}

void *producer (void *arg) {
    ThreadArg *threadArg = (ThreadArg*) arg;
    randomizeIntArray(threadArg->numbers, BUFFER_SIZE);
    randomizeCharArray(threadArg->letters, BUFFER_SIZE);

    return NULL;
}

void *consumer (void *arg) {
    ResultSet *resultSet = (ResultSet *) arg;
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        if (resultSet->input->numbers[i] % 2 == 0) {
            resultSet->resultCount++;
            printf("input %d:%d\n",i ,resultSet->input->numbers[i]);
            resultSet->results[i] = resultSet->input->numbers[i];
        }
    }
    removeEvens(resultSet->input->numbers);
    return NULL;
}


int main (int argc, char *argv[]) {
    srand(time(NULL));
    pthread_t producerId;
    pthread_t consumerId;

    ThreadArg threadArg = {{}, {}};

    pthread_create(&producerId, NULL, producer, (void*) &threadArg);
    ResultSet resultSet = {&threadArg, {}, 0};
    pthread_create(&consumerId, NULL, consumer, (void *) &resultSet);

    pthread_join(producerId, NULL);
    pthread_join(consumerId, NULL);



    intArrayToString(threadArg.numbers, BUFFER_SIZE); //, numericString, MAX_STRING_LENGTH);
    printf("letters:%s\n", threadArg.letters);

    printf("EVENS\n------------\n");
    for (int i = 0; i < resultSet.resultCount ; ++i) {
        printf("%d\n", resultSet.results[i]);
    }
    printf("initial:%d, ", %d{} %d: i < t)

    return 0;
}
