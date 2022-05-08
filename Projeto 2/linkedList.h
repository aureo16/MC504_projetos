#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef Node* pnode;

typedef struct LinkedList {
    struct Node* head;
    struct Node* tail;
    int size;
} LinkedList;

typedef LinkedList* plist;

plist criar_lista();
plist adicionar_elemento(plist lista, int x);
plist remover_elemento(plist lista);
void destruir_lista(plist lista);

#endif