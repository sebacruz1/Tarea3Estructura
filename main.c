#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "heap.h"
#include "heap.c"

void agregarTarea(Heap *tareas)
{
    char *nombre = malloc(sizeof(char) * 100);
    int prioridad = 0;
    printf("Ingrese el nombre de la tarea: ");
    scanf("%s", nombre);
    printf("Ingrese la prioridad de la tarea: ");
    scanf("%d", &prioridad);
    heap_push(tareas, nombre, prioridad);
}


void mostrarTareas(Heap *tareas)
{
    Heap *aux = createHeap(compareMin);
    if (aux == NULL)
    {
        printf("Error al crear el heap auxiliar\n");
        return;
    }

    if (tareas->size == 0)
    {
        printf("No hay tareas por hacer\n");
        return;
    }

    printf("Tareas por hacer:\n");

    while (tareas->size > 0)
    {
        heapElem tarea = tareas->heapArray[0];
        printf("%s ", tarea.nombre);
        printf("Prioridad: %d", tarea.priority);
        if (tarea.tareaPrecedente != NULL)
        {
            printf(" - Precedente: %s\n", tarea.tareaPrecedente);
        }
        else 
        {
            printf("\n");
        }
        heap_push(aux, tarea.nombre, tarea.priority);
        heap_pop(tareas);
    }

    while (aux->size > 0)
    {
        heapElem tarea = aux->heapArray[0];
        heap_push(tareas, tarea.nombre, tarea.priority);
        heap_pop(aux);
    }

    free(aux);
}



int main()
{
    int opcion = 0;
    Heap *tareas = createHeap(compareMin);
    if (tareas == NULL)
    {
        printf("Error al crear el heap\n");
        return 1;
    }

    do 
    {
        printf("Seleccione Una Opcion:\n");
        printf("1.- Agregar Tarea\n");
        printf("2.- Establecer precedencia entre tareas\n");
        printf("3.- Mostrar tareas por hacer\n");
        printf("4.- Marcar tarea como completada\n");
        printf("5.- Deshacer última acción\n");
        printf("6.- Cargar datos de tarea desde un archivo de texto\n"); 
        printf("0.- Salir\n");

        scanf("%d", &opcion);

        switch (opcion)
        {
            case 1:
                agregarTarea(tareas);
                break;
            case 2:
                break;
            case 3:
                mostrarTareas(tareas);
                break;
        
            case 0: 
                printf("Saliendo...\n");
                return 0;
            default:
                printf("Opcion no valida\n");
                break;
        }

    } while (opcion != 0);

    return 0;
}