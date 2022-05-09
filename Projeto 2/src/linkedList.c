#include "linkedList.h"

plist criar_lista(){
    plist lista = malloc(sizeof(LinkedList));
    lista->head = NULL;
    lista->size = 0;
    lista->tail = NULL;
    return lista;
}

plist adicionar_elemento(plist lista, int x){
   pnode newNode = malloc(sizeof(Node));
   newNode->data = x;
   newNode->next = NULL;
   if (lista->size == 0) {
       lista->head = newNode;
       lista->tail = newNode;
   }
   else{
    lista->tail->next = newNode;
    lista->tail = newNode;
   }
   
   lista->size++;

   return lista;
}

plist remover_elemento(plist lista) {
    pnode primeiro = lista->head;
    lista->head = lista->head->next;
    lista->size--;
    free(primeiro);

    return lista;
}

void destruir_lista(plist lista){
    free(lista);
}