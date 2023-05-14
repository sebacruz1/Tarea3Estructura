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
  int (*comparator)(const void*, const void*);
} Heap;

void* heap_top(Heap* pq)
{
  if (pq->size == 0) return NULL;
  
  return pq->heapArray[pq->size - 1].nombre;
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

    if (pq->comparator(&pq->heapArray[posicion], &pq->heapArray[padre]) >= 0) break;

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

    if (hijoDer < pq->size && pq->comparator(&pq->heapArray[hijoDer], &pq->heapArray[hijoIzq]) < 0)
      hijoMayor = hijoDer;

    if (pq->comparator(&pq->heapArray[hijoMayor], &pq->heapArray[posicion]) >= 0) break;

    heapElem aux = pq->heapArray[posicion];
    pq->heapArray[posicion] = pq->heapArray[hijoMayor];
    pq->heapArray[hijoMayor] = aux;

    posicion = hijoMayor;
  }
}

int compareMin(const void* a, const void* b) {
  const heapElem* elemA = (const heapElem*) a;
  const heapElem* elemB = (const heapElem*) b;
  
  if (elemA->priority < elemB->priority) return -1;
  if (elemA->priority > elemB->priority) return 1;
  return 0;
}

Heap* createHeap(int (*comparator)(const void*, const void*))
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
  new->comparator = comparator; // Nuevo campo

  return new;
}

