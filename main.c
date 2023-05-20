#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include "Map.h"
#include "stack.h"
#include <stdlib.h>
typedef struct tarea
{
    char* nombre;
    int prioridad;
    List *dependencias;
    int cantDependencias;
    bool visitada;
    Stack *undo;
    int cantUndos;
} tareas;

int is_equal_string(void *key1, void *key2)
{
    if (strcmp((char *)key1, (char *)key2) == 0)
    {
        return 1;
    }
    return 0;
}

void agregarTarea(Map *mapaTareas)
{
    tareas *tarea = (tareas *)malloc(sizeof(tareas));
    char nombreTarea[50];
    int prioridadTarea = 0;
    tarea->visitada = false;

    printf("Ingrese el nombre de la tarea: ");
    scanf("%s", nombreTarea);
    printf("Ingrese la prioridad de la tarea: ");
    scanf("%d", &prioridadTarea);

    tarea->prioridad = prioridadTarea;
    tarea->nombre = nombreTarea;
    tarea->cantDependencias = 0;
    tarea->dependencias = createList();
    tarea->undo = stack_create();
    tarea->cantUndos = 0;

    insertMap(mapaTareas, tarea->nombre, tarea);
}

void establecerPrecedencia(Map *mapaTareas)
{
    char nombreTarea[50];
    char nombreDependencia[50];
    printf("Ingrese el nombre de la tarea: ");
    scanf("%s", nombreTarea);
    printf("Ingrese el nombre de la dependencia: ");
    scanf("%s", nombreDependencia);

    tareas *tarea = searchMap(mapaTareas, nombreTarea);
    tareas *dependencia = searchMap(mapaTareas, nombreDependencia);

    if (tarea != NULL && dependencia != NULL)
    {
        stack_push(tarea->undo, tarea);
        tarea->cantUndos++;
        pushBack(tarea->dependencias, dependencia);
        tarea->cantDependencias++;

    }
    else
    {
        printf("No se encontro la tarea o la dependencia\n");
    }
}

void marcarTareaPorHacer(Map *mapaTareas)
{
    char nombreTarea[50];
    printf("Ingrese el nombre de la tarea: ");
    scanf("%s", nombreTarea);

    tareas *tarea = searchMap(mapaTareas, nombreTarea);
    if (tarea != NULL)
    {
        eraseMap(mapaTareas, tarea->nombre);
        stack_push(tarea->undo, tarea);
        tarea->cantUndos++;
    }
    else
    {
        printf("No se encontro la tarea\n");
    }
}

void marcarTareaComoCompletada(Map *mapaTareas)
{
    char nombreTarea[50];
    printf("Ingrese el nombre de la tarea: ");
    scanf("%s", nombreTarea);

    tareas *tarea = searchMap(mapaTareas, nombreTarea);
    if (tarea != NULL)
    {
        stack_push(tarea->undo, tarea);
        tarea->cantUndos++;
        eraseMap(mapaTareas, tarea->nombre);
    }
    else
    {
        printf("No se encontro la tarea\n");
    }
}

void deshacerUltimaAccion(Map *mapaTareas)
{
    char nombreTarea[50];
    printf("Ingrese el nombre de la tarea: ");
    scanf("%s", nombreTarea);

    tareas *tarea = searchMap(mapaTareas, nombreTarea);
    if (tarea != NULL)
    {
        if (tarea->cantUndos > 0)
        {
            tareas *tareaUndo = stack_pop(tarea->undo);
            insertMap(mapaTareas, tareaUndo->nombre, tareaUndo);
        }
        else
        {
            printf("No hay acciones para deshacer\n");
        }
    }
    else
    {
        printf("No se encontro la tarea\n");
    }
}

int main()
{
    int opcion = 0;
    Map *mapaTareas = createMap(is_equal_string);
    

    if (mapaTareas == NULL)
    {
        printf("Error al crear el mapa\n");
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
                agregarTarea(mapaTareas);            
                break;
            case 2:
                establecerPrecedencia(mapaTareas);
                break;
            case 3:
                //mostrarTareasPorHacer(mapaTareas);
                break;
            case 4:
                marcarTareaComoCompletada(mapaTareas);
                break;
            case 5:
                deshacerUltimaAccion(mapaTareas);
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