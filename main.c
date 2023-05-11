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
    tareas->size++;
}

void mostrarTareas(Heap *tareas)
{
    printf("Tareas por hacer:\n");
    for (int i = 0; i < tareas->size; i++)
    {
        if (tareas->heapArray[i].nombre != NULL)
            printf("%s, %d\n", tareas->heapArray[i].nombre, tareas->heapArray[i].priority);
    }
}

int main()
{
    int opcion = 0;
    Heap *tareas = createHeap();

    do 
    {
        printf("Seleccione Una Opcion:\n");
        printf("1.- Agregar Tarea\n");
        printf("2.- Establecer precedencia entre tareas\n");
        printf("3.- Mostrar tareas por hacer\n");
        printf("4.- Marcar tarea como completada");
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