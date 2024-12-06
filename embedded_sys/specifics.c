/*
32 bit single core controler
some sram at 0x1000
I want to use 128 bit of sram as a bitmap
write a function to test ad flip
if bit is set, clear
if bit is clear set it
in both cases return boolean old value
*/
#include <stdio.h>
#include <stdlib.h>

#define BIT_SIZE 32

uint8_t test_and_flip (volatile uint32_t* pmemstart, uint8_t bit){
    int mapIndex = bit / BIT_SIZE;
    int bitIndex = bit % BIT_SIZE;
    volatile uint32_t* word = &pmemstart[mapIndex];
    uint8_t oldValue = (*word & (1 << bitIndex)) != 0;
    *word ^= 1 << bitIndex;
    return oldValue;
}

int main(){
    volatile uint32_t bitmap[4] = {0};

    uint8_t old_value = test_and_flip(bitmap, 127);
    printf("Old value: %d, New word value: 0x%X\n", old_value, bitmap[3]);

    return 0;
}