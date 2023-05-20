#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include "Map.h"
#include "stack.h"
#include "heap.h"
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

const char *get_csv_field (char * tmp, int k) 
{
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while (tmp[i+1]!='\0'){

        if (tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if (open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if (tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if (k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }

    return NULL;
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

void mostrarTareasPorHacer(Map *mapaTareas)
{
    Heap *heap = createHeap();
    tareas *tarea = malloc(sizeof(tareas));
    int aux = 0;
    while (tarea != NULL)
    {
        tarea = firstMap(mapaTareas);
        if (tarea == NULL) break;
        if (tarea->cantDependencias == 0)
            tarea->visitada = true;
            aux++;
        
        tarea = nextMap(mapaTareas);
    }

    for (int i = 0; i < aux; i++)
    {
        pushBack(listaOrdenada, heap_top(mapaTareas));
        heap_pop(mapaTareas);
    }

    while (1)
    {
        tarea = firstMap(mapaTareas);
        if (tarea == NULL) break;
        if (tarea->visitada == false)
        {
            for (int i = 0; i < tarea->cantDependencias; i++)
            {
                tareas *dependencia = first(tarea->dependencias);
                if (dependencia->visitada == false)
                {
                    tarea->visitada = true;
                    pushBack(listaOrdenada, tarea);
                    break;
                }
                else
                {
                    tarea->visitada = true;
                    pushBack(listaOrdenada, tarea);
                }
            }
        }
        tarea = nextMap(mapaTareas);
        
    }

}




/*void mostrarTareas(Map *mapaTareas)
{
    Heap *heap = createHeap();
    tareas *tarea = malloc(sizeof(tareas));
    int aux = 0;
    while (tarea != NULL)
    {
        tarea = firstMap(mapaTareas);
        if (tarea == NULL) break;
        if (tarea->cantDependencias == 0)
            tarea->visitada = true;
            aux++;
        
        tarea = nextMap(mapaTareas);
    }

    for (int i = 0; i < aux; i++)
    {
        pushBack(listaOrdenada, heap_top(heapTareas));
        heap_pop(heapTareas);
    }

    while (1)
    {
        tarea = firstMap(mapaTareas);
        if (tarea == NULL) break;
        if (tarea->visitada == false)
        {
            for (int i = 0; i < tarea->cantDependencias; i++)
            {
                tareas *dependencia = first(tarea->dependencias);
                if (dependencia->visitada == false)
                {
                    tarea->visitada = true;
                    pushBack(listaOrdenada, tarea);
                    break;
                }
                else
                {
                    tarea->visitada = true;
                    pushBack(listaOrdenada, tarea);
                }
            }
        }
        tarea = nextMap(mapaTareas);
        
    }

}*/


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

void cargarDatos(Map *mapaTareas)
{
    char nombre[20];
    tareas *tarea = malloc(sizeof(tarea));
    printf("Ingrese el nombre del archivo: ");
    scanf("%s", nombre);
    strcat(nombre, ".cvs");

    FILE *fp = fopen(nombre, "r");

    if (fp == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    char linea[1024];
    int k;
    
    while (fgets(linea, 1023, fp) != NULL)
    {
        for (int i = 0; i < 3; i++)
        {
            const char *tmp = get_csv_field(linea, i);
            if (i == 0)
            {
                tarea->nombre = (char *)tmp;
            }
            else if (i == 1)
            {
                tarea->prioridad = atoi(tmp);
            }
            else
            {
                tarea->dependencias = createList();
                pushBack(tarea->dependencias, tmp);
                tarea->cantDependencias++;
            }
            insertMap(mapaTareas, tarea->nombre, tarea);
        }
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
            case 6: 
                cargarDatos(mapaTareas);
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
