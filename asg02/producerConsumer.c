#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define BUFFER_SIZE 16
#define FLOOR -100
#define CEILING 100
#define MAX_STRING_LENGTH 512
#define BASE_ASCII_CHARACTER '<'
#define ASCII_CODE_FLOOR 60
#define ASCII_CODE_CEILING 126

typedef struct _threadArg {
    char letters[BUFFER_SIZE];
    int numbers[BUFFER_SIZE];
} ThreadArg;
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
//    char string[MAX_STRING_LENGTH] = {0};
//    strcpy(string, "");
    for (int i = 0; i < intArraySize; ++i) {
        char buf[4];
        int n = sprintf( buf, "%d", intArray[i]);
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
        int offset = (int) (rand() % (ASCII_CODE_CEILING - ASCII_CODE_FLOOR + 1) + ASCII_CODE_FLOOR);
        array[i] = rand() % (ASCII_CODE_CEILING - ASCII_CODE_FLOOR + 1) + ASCII_CODE_FLOOR;
//        printf("array[%d]=%c\n", i, array[i]);
    }
}

void *producer (void *arg) {
    ThreadArg *threadArg = (ThreadArg*) arg;
    randomizeIntArray(threadArg->numbers, BUFFER_SIZE);
    randomizeCharArray(threadArg->letters, BUFFER_SIZE);
}

void *consumer (void *arg) {
    ThreadArg *threadArg = (ThreadArg*) arg;

}


int main (int argc, char *argv[]) {
    srand(time(NULL));
    pthread_t threadId;
    ThreadArg threadArg = {{}, {}};
    pthread_create(&threadId, NULL, producer, (void*) &threadArg);
    pthread_join( threadId, NULL);

//    char numericString[MAX_STRING_LENGTH];
    intArrayToString(threadArg.numbers, BUFFER_SIZE); //, numericString, MAX_STRING_LENGTH);
    printf("letters:%s\n", threadArg.letters);
//    printf("numbers:%s\n", numericString);

    return 0;
}
