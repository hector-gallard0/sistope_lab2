#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* data;
    struct Node* next;    
} Node;

typedef struct LinkedList {
    Node* head;
    Node* tail;
    int size;
} LinkedList;

LinkedList* createLinkedList();

int getSize(LinkedList* list);

char* get(LinkedList* list, int position);

void append(LinkedList* list, const char* data);

void printLinkedList(LinkedList* list);

void freeLinkedList(LinkedList* list);

// Entradas: Estado y letra leida.
// Salidas: No hay. 
// Descripción: Dependiendo de la letra leída, se pasa a uno u otro estado, siguiendo el diagrama del AFN del enunciado. Por ejemplo: Si se está en el estado inicial, para pasar al estado 2 se debe leer la letra 'G', cualquier otra letra mantiene el estado en 1 (inicial).
void reconocedor(int *estado, char letra);