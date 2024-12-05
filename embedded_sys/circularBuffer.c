#include <stdio.h>
#include <stdlib.h>
#include "circularBuffer.h"

void initBuffer(){
    buffer.isFull = 0;
    buffer.isEmpty = 1;
    buffer.head = 0;
    buffer.tail = 0;
    for(int i = 0; i < CIRCULAR_BUF_SIZE; i ++){
        buffer.buf[i] = 0;
    }
}
eBUF_ACTION_STATUS addElement(int num){
    eBUF_ACTION_STATUS ret = BUF_ADD_OK;
    if (buffer.isFull){
        int garbageElement;
        readElement(&garbageElement);
    }
    buffer.buf[buffer.head] = num;
    buffer.head = (buffer.head + 1) % CIRCULAR_BUF_SIZE;
    if (buffer.head == buffer.tail){
        buffer.isFull = 1;
    }   
    buffer.isEmpty = 0;
    return ret;
}

eBUF_ACTION_STATUS readElement(int *num){
    eBUF_ACTION_STATUS ret = BUF_READ_OK;
    if (buffer.isEmpty){
        ret = BUF_READ_FAILED;
        return ret;
    }
    *num = buffer.buf[buffer.tail];
    buffer.tail = (buffer.tail + 1) % CIRCULAR_BUF_SIZE;
    if (buffer.head == buffer.tail){
        buffer.isEmpty = 1;
    }   
    buffer.isFull = 0;

    return ret;
}

void printBuffer(){
    printf("[");
    for(int i = 0; i < CIRCULAR_BUF_SIZE; i++){
        printf("%d ", buffer.buf[i]);
    }
    printf("]\n");
}
// int main(){
//     addElement(0);
//     addElement(1);
//     addElement(2);
//     addElement(3);
//     addElement(4);
//     addElement(5);
//     addElement(6);
//     int val = 0;
//     readElement(&val);
//     printf("%d\n", val);
//     addElement(5);
//     readElement(&val);
//     printf("%d\n", val);
//     readElement(&val);
//     printf("%d\n", val);
//     readElement(&val);
//     printf("%d\n", val);
//     readElement(&val);
//     printf("%d\n", val);
//     readElement(&val);
//     printf("%d\n", val);
//     return 0;
// }