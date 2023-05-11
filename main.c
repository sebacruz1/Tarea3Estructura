#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int opcion = 0;

    do 
    {
        printf("Seleccione Una Opcion:\n");
        printf("1.- Agregar Tarea\n");
        printf("2.- Establecer precedencia entre tareas\n");
        printf("3.- Mostrar tareas por hacer\n");
        printf("4.- Marcar tarea como completada");
        printf("5.- Deshacer última acción\n");
        printf("6.- Cargar datos de tarea desde un archivo de texto"); 
        printf("0.- Salir\n");

        scanf("%d", &opcion);

        switch (opcion)
        {
            case 1:
                agregarTarea();
                break;
            default:
                printf("Opcion no valida\n");
                break;
        }
    } while (opcion != 0);
}