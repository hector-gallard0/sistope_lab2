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

int getSize(LinkedList* list) {
    return list->size;
}

char* get(LinkedList* list, int position) {
    if (position < 0 || position >= getSize(list)) {
        return NULL; // La posición está fuera de los límites de la lista
    }

    Node* current = list->head;
    for (int i = 0; i < position; i++) {
        current = current->next;
    }

    return current->data;
}

LinkedList* createLinkedList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0; // Inicializar el tamaño en 0
    return list;
}

void append(LinkedList* list, const char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = strdup(data);
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }

    list->size++;
}

void printLinkedList(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

void freeLinkedList(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    free(list);
}

// Entradas: Estado y letra leida.
// Salidas: No hay. 
// Descripción: Dependiendo de la letra leída, se pasa a uno u otro estado, siguiendo el diagrama del AFN del enunciado. Por ejemplo: Si se está en el estado inicial, para pasar al estado 2 se debe leer la letra 'G', cualquier otra letra mantiene el estado en 1 (inicial).
void reconocedor(int *estado, char letra){
    if(*estado == 1){
        if(letra == 'G'){
            *estado = 2;
        }
    }
    else if(*estado == 2){
        if(letra == 'T'){
            *estado = 3;
        }        
        else if(letra == 'A' || letra == 'C'){
           *estado = 1;         
        }
    }
    else if(*estado == 3){
        if(letra == 'C'){
            *estado = 4;
        }
        else if(letra == 'G'){
            *estado = 2;
        }
        else if(letra == 'A'){
            *estado = 1;
        }
    }
}