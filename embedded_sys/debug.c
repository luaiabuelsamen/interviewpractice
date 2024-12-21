#include <stdio.h>
#include <stdlib.h>

static uint16_t buffer[32U];
static uint16_t index = 0;
static uint16_t average = 0;

void task_1000HZ(){
    buffer[index] = readADC();
    if (index++ > 31U)
        index = 0;
}

void task_100HZ(){
    average = buffer[index] + buffer[index - 1U] + buffer[index - 2U] / 3;
}