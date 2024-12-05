#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "circularBuffer.h"
#include <string.h>

#define MS_500 500000
#define MS_100 100000

static volatile int sensorValue = 0;
pthread_mutex_t sensorMutex;

int read_sensor() {
    return rand() % 100;
}

void* updateSensor500ms(void* arg) {
    while(1){
        int new_value =  read_sensor();
        if(pthread_mutex_lock(&sensorMutex) == 0){
            addElement(new_value);
            sensorValue = new_value;
            pthread_mutex_unlock(&sensorMutex);
        } else{
            printf("Could not acquire mutex");
        }

        usleep(MS_500);
    }
    return NULL;
}

void* getSensorValue(void* arg){
    while(1){
        static int getValue= 0;
        if(pthread_mutex_lock(&sensorMutex) == 0){
            readElement(&getValue);
            pthread_mutex_unlock(&sensorMutex);
        } else{
            printf("Could not acquire mutex");
        }

        printf("Sensor value: %d\n", getValue);
        usleep(MS_100);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    if(pthread_mutex_init(&sensorMutex, NULL) != 0){
        printf("Could not initialize mutex");
        return EXIT_FAILURE;
    }
    initBuffer();
    if (pthread_create(&thread1, NULL, updateSensor500ms, NULL)) {
        fprintf(stderr, "Error creating thread 1\n");
        return EXIT_FAILURE;
    }
    if (pthread_create(&thread2, NULL, getSensorValue, NULL)) {
        fprintf(stderr, "Error creating thread 2\n");
        return EXIT_FAILURE;
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("All threads have completed execution.\n");
    pthread_mutex_destroy(&sensorMutex);
    return EXIT_SUCCESS;
}
