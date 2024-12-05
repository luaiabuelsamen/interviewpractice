#include <stdio.h>
#include <stdlib.h>

#define PARENT(i)      ((i - 1)/2)
#define LEFT_CHLD(i)   (i * 2 + 1)
#define RIGHT_CHILD(i) (i * 2 + 2)

typedef struct heap {
    int capacity;
    int index;
    int* heap;
} heapq, *pHeapq;

pHeapq initHeapq(int capacity){
    pHeapq maxq = (pHeapq) malloc(sizeof(heapq));
    maxq->capacity = capacity;
    maxq->heap = (int *) malloc(sizeof(int) * capacity);
    maxq->index = 0;
    return maxq;
}

void swap(int* a, int* b){
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

int getMax(pHeapq maxq){
    if(maxq->index == 0){
        printf("heapq is empty\n");
        return -1;
    }
    return maxq->heap[0];
}

void upHeapify(pHeapq maxq,int index){
    if(index == 0 || maxq->heap[index] <= maxq->heap[PARENT(index)]){
        return;
    }
    swap(&maxq->heap[index], &maxq->heap[PARENT(index)]);
    upHeapify(maxq, PARENT(index));
}

void downHeapify(pHeapq maxq,int index){
    int left_child = LEFT_CHLD(index);
    int right_child = RIGHT_CHILD(index);
    int present_index = index;

    if(left_child < maxq->index &&  maxq->heap[left_child] > maxq->heap[index]){
        present_index = left_child;
    }

    if(right_child < maxq->index &&  maxq->heap[right_child] > maxq->heap[index]){
        present_index = right_child;
    }

    if(present_index == index){
        return;
    }

    swap(&maxq->heap[index], &maxq->heap[present_index]);
    downHeapify(maxq, present_index);

}

void push(pHeapq maxq, int val){
    if(maxq->index == maxq->capacity){
        printf("heapq is full\n");
        return;
    }
    maxq->heap[maxq->index] = val;
    upHeapify(maxq, maxq->index);
    maxq->index++;
}

int pop(pHeapq maxq){
    if(maxq->index == 0){
        printf("heapq is empty\n");
        return -1;
    }
    int ret = maxq->heap[0];
    maxq->index--;
    maxq->heap[0] = maxq->heap[maxq->index];
    downHeapify(maxq, 0);
    return ret;
}

void printArray(pHeapq heapq){
    printf("[");
    for (int i = 0; i < heapq->capacity; i++) {
        printf("%d ", heapq->heap[i]);
    }
    printf("]");
    printf("\n");
}
int main(){
    pHeapq maxq = initHeapq(5);
    push(maxq, 0);
    push(maxq, 1);
    push(maxq, 10);
    push(maxq, 2);
    push(maxq, 3);
    push(maxq, 4);
    printArray(maxq);
    int curMax = getMax(maxq);
    printf("%d\n", curMax);
    curMax = pop(maxq);
    printf("%d\n", curMax);
    curMax = pop(maxq);
    printf("%d\n", curMax);
    curMax = pop(maxq);
    printf("%d\n", curMax);
    return 0;
}