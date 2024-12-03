#include <stdio.h>
#include <stdlib.h>

#define CIRCULAR_BUF_SIZE 5

typedef struct sCircularBuffer{
    int buf[CIRCULAR_BUF_SIZE];
    int isFull;
    int isEmpty;
    int head;
    int tail;
} sCircularBuffer;

static sCircularBuffer buffer;

typedef enum {
    BUF_ADD_OK = 0,
    BUF_READ_OK = 1,
    BUF_ADD_FAILED = 2,
    BUF_READ_FAILED = 3
} eBUF_ACTION_STATUS;

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
        ret = BUF_ADD_FAILED;
        return ret;
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

int main(){
    addElement(0);
    addElement(1);
    addElement(2);
    addElement(3);
    addElement(4);
    addElement(5);
    addElement(6);
    int val = 0;
    readElement(&val);
    printf("%d\n", val);
    addElement(5);
    readElement(&val);
    printf("%d\n", val);
    readElement(&val);
    printf("%d\n", val);
    readElement(&val);
    printf("%d\n", val);
    readElement(&val);
    printf("%d\n", val);
    readElement(&val);
    printf("%d\n", val);
    return 0;
}