#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMBRE 50
#define ARCHIVO "inventario.txt"

typedef struct {
    char nombre[MAX_NOMBRE];
    float precio;
    int cantidad;
} Producto;

Producto* cargarInventario(int *numProductos);
void agregarProducto(Producto **inventario, int *numProductos);
void guardarInventario(Producto *inventario, int numProductos);
void imprimirInventario(Producto *inventario, int numProductos);

void main(void) {
    int numProductos = 0;
    Producto *inventario = cargarInventario(&numProductos);

    printf("Inventario cargado. Productos actuales: %d\n", numProductos);

    char opcion;
    printf("\nDesea agregar un nuevo producto? (s/n): ");
    scanf(" %c", &opcion);

    if (opcion == 's' || opcion == 'S') {
        agregarProducto(&inventario, &numProductos);
        guardarInventario(inventario, numProductos);
        printf("Producto agregado y archivo actualizado.\n");
    }

    printf("\nDesea imprimir los productos en inventario? (s/n): ");
    scanf(" %c", &opcion);

    if (opcion == 's' || opcion == 'S') {
        imprimirInventario(inventario, numProductos);
    }

    free(inventario);
    return 0;
}

Producto* cargarInventario(int *numProductos) {
    FILE *archivo = fopen(ARCHIVO, "r");
    if (!archivo) {
        printf("No se encontro el archivo '%s'. Se creara uno nuevo.\n", ARCHIVO);
        *numProductos = 0;
        return NULL;
    }

    Producto temp;
    Producto *inventario = NULL;

    while (fscanf(archivo, "%s %f %d", temp.nombre, &temp.precio, &temp.cantidad) == 3) {
        inventario = realloc(inventario, (*numProductos + 1) * sizeof(Producto));
        inventario[*numProductos] = temp;
        (*numProductos)++;
    }

    fclose(archivo);
    return inventario;
}

void agregarProducto(Producto **inventario, int *numProductos) {
    Producto nuevo;

    printf("Nombre del producto: ");
    scanf("%s", nuevo.nombre);

    printf("Precio: ");
    scanf("%f", &nuevo.precio);

    printf("Cantidad: ");
    scanf("%d", &nuevo.cantidad);

    *inventario = realloc(*inventario, (*numProductos + 1) * sizeof(Producto));
    (*inventario)[*numProductos] = nuevo;
    (*numProductos)++;
}

void guardarInventario(Producto *inventario, int numProductos) {
    FILE *archivo = fopen(ARCHIVO, "w");
    if (!archivo) {
        printf("Error al abrir el archivo para guardar.\n");
        return;
    }

    for (int i = 0; i < numProductos; i++) {
        fprintf(archivo, "%s %.2f %d\n",
                inventario[i].nombre,
                inventario[i].precio,
                inventario[i].cantidad);
    }

    fclose(archivo);
}

void imprimirInventario(Producto *inventario, int numProductos) {
    if (numProductos == 0) {
        printf("No hay productos en inventario.\n");
        return;
    }

    printf("\n--- INVENTARIO ---\n");
    for (int i = 0; i < numProductos; i++) {
        printf("%d. %s - $%.2f - %d unidades\n",
               i + 1,
               inventario[i].nombre,
               inventario[i].precio,
               inventario[i].cantidad);
    }
}
