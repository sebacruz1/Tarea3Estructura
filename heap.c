#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* nombre;
   int priority;
   void* tareaPrecedente;
} heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capacity;
} Heap;

void* heap_top(Heap* pq)
{
  if (pq->size == 0) return NULL;
  
  return pq->heapArray[0].nombre;
}

void heap_push(Heap* pq, void* nombre, int priority)
{
  if (pq->size >= pq->capacity)
  {
    pq->capacity = pq->capacity * 2 + 1;
    pq->heapArray = realloc(pq->heapArray, sizeof(heapElem) * pq->capacity); 
    if (!pq->heapArray) {
      printf("Error: no se pudo expandir el heap.\n");
      exit(EXIT_FAILURE);
    }
  }
  
  int posicion = pq->size;
  pq->heapArray[posicion].nombre = nombre;
  pq->heapArray[posicion].priority = priority;
  pq->size++;

  while (posicion > 0)
  {
    int padre = (posicion - 1) / 2;

    if (pq->heapArray[posicion].priority <= pq->heapArray[padre].priority) break;

    heapElem aux = pq->heapArray[posicion];
    pq->heapArray[posicion] = pq->heapArray[padre];
    pq->heapArray[padre] = aux;

    posicion = padre;
  }
}

void heap_pop(Heap* pq)
{
  if (pq->size == 0) return;

  pq->heapArray[0] = pq->heapArray[pq->size - 1];
  pq->size--;

  int posicion = 0;

  while (posicion < pq->size)
  {
    int hijoIzq = 2 * posicion + 1;
    int hijoDer = 2 * posicion + 2;

    if (hijoIzq >= pq->size) break;

    int hijoMayor = hijoIzq;

    if (hijoDer < pq->size && pq->heapArray[hijoDer].priority > pq->heapArray[hijoIzq].priority)
      hijoMayor = hijoDer;

    if (pq->heapArray[hijoMayor].priority <= pq->heapArray[posicion].priority) break;

    heapElem aux = pq->heapArray[posicion];
    pq->heapArray[posicion] = pq->heapArray[hijoMayor];
    pq->heapArray[hijoMayor] = aux;

    posicion = hijoMayor;
  }
}

Heap* createHeap()
{
  Heap* new = malloc(sizeof(Heap)); 
  if (!new) {
    printf("Error: no se pudo crear el heap.\n");
    exit(EXIT_FAILURE);
  }

  new->heapArray = malloc(3 * sizeof(heapElem));
  if (!new->heapArray) {
    printf("Error: no se pudo crear el array del heap.\n");
    exit(EXIT_FAILURE);
  }

  new->size = 0;  
  new->capacity = 3;

  return new;
}
