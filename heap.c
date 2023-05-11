#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;


void* heap_top(Heap* pq)
{
  if (pq->size == 0) return NULL;
  
  void *top = pq->heapArray[0].data;
  return top;
}

void heap_push(Heap* pq, void* data, int priority)
{
  heapElem aux;
  if (pq->size >= pq->capac)
  {
    pq->capac = pq->capac * 2 + 1;
    pq->heapArray = realloc(pq->heapArray, sizeof(heapElem) * pq->capac); 
    
  }
  
  if (pq->size == 0)
  {
    pq->heapArray[0].data = data;
    pq->heapArray[0].priority = priority;
    pq->size++;
    return; 
  }
  
  pq->heapArray[pq->size].data = data;
  pq->heapArray[pq->size].priority = priority;
  int posicion = pq->size;
  int padre = (posicion - 1) / 2;

  while (pq->heapArray[posicion].priority > pq->heapArray[padre].priority)
  {
    if (pq->heapArray[posicion].priority > pq->heapArray[padre].priority)
    {
      aux = pq->heapArray[posicion];
      pq->heapArray[posicion] = pq->heapArray[padre];
      pq->heapArray[padre] = aux;
      posicion = padre;
      padre = (posicion - 1) / 2;
    }
  }
  
  pq->size++;
}

void heap_pop(Heap* pq)
{
  if (pq->size == 0)
        return;
    pq->heapArray[0] = pq->heapArray[pq->size - 1];
    pq->size--;
    int posicion = 0;
    while (1)
    {
        int hijoIzq = 2 * posicion + 1;
        int hijoDer = 2 * posicion + 2;
        if (hijoIzq >= pq->size && hijoDer >= pq->size)
            break;
        heapElem aux;
        int hijoMayor = hijoIzq;
        if (hijoDer < pq->size && pq->heapArray[hijoDer].priority > pq->heapArray[hijoIzq].priority)
            hijoMayor = hijoDer;
        if (pq->heapArray[hijoMayor].priority > 
            pq->heapArray[posicion].priority)
        {
            aux = pq->heapArray[hijoMayor];
            pq->heapArray[hijoMayor] = pq->heapArray[posicion];
            pq->heapArray[posicion] = aux;
            posicion = hijoMayor;
        }
        else
        {
            break;
        }
    }
}


Heap* createHeap()
{
  Heap *new; 
  new = malloc(3 * sizeof(Heap));
  new->heapArray = malloc(3 * sizeof(Heap));
  new->size = 0; 
  new->capac = 3;

  return new;
}