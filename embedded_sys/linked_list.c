#include <stdio.h>
#include <stdlib.h>


typedef struct node{
    int val;
    struct node * next;
} node;

node* createNode(int val){
    node* newNode = (node *) malloc(sizeof(node));
    newNode->val = val;
    if (newNode == NULL){
        return newNode;
    }
    return newNode;
}

void addNode(node* head, int val){
    node* current = head;
    while(current->next != NULL){
        current = current->next;
    }
    node* new_node = createNode(val);
    current->next = new_node;
}

void insertNode(node** head, int index, int val){
    node* new_node = createNode(val);
    if (index == 0){
        node* next = *head;
        new_node->next = next;
        *head = new_node;
        return;
    }
    node* cur = * head;
    int i = 0;
    while(cur->next != NULL && i < index - 1){
        cur = cur->next;
        i++;
    }
    node* rest = cur->next;
    cur->next = new_node;
    new_node->next = rest;
}

void printList(node* head){
    node* cur = head;
    while(cur != NULL){
        printf("%d->", cur->val);
        cur = cur->next;
    }
    printf("\n");
}

void deleteAllOccurences(node **head, int val){
    while(*head != NULL && (*head)->val == val){
        node *temp =  *head;
        *head = (*head)->next;
        free(temp);
    }
    if(*head == NULL){
        return;
    }

    node *cur = *head;
    while(cur->next){
        if (cur->next->val == val){
            node* next = cur->next;
            cur->next = cur->next->next;
            free(next);
        }
        else {
            cur = cur->next;
        }
    }
}

int main(){

    node* head = createNode(0);
    addNode(head, 1);
    addNode(head, 2);
    addNode(head, 2);
    addNode(head, 2);
    addNode(head, 3);
    addNode(head, 4);
    printList(head);
    deleteAllOccurences(&head, 2);
    printList(head);
    insertNode(&head, 2, 2);
    printList(head);
    return 0;
}