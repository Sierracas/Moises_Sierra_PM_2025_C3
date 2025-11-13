#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRLEN 128

typedef struct {
    int id;
    char marca[50];
    char modelo[50];
    int ano;
    char placa[20];
    double consumo_ciudad;
    double consumo_carretera;
    double costo_seguro_ano;
    double costo_cambio_por_km;
    int tiempo_depreciacion_anos;
    double costo_vehiculo;
    double km_promedio_ano;
    double costo_limpieza;
} Vehiculo;

typedef struct {
    int id;
    char nombre[40];
    double precio_por_litro;
} Combustible;

void menu();
void agregarVehiculo(Vehiculo **arr, int *n);
void listarVehiculos(Vehiculo *arr, int n);
void modificarVehiculo(Vehiculo *arr, int n);
void agregarCombustible(Combustible **arr, int *n);
void listarCombustible(Combustible *arr, int n);
void modificarCombustible(Combustible *arr, int n);
void calcularViaje(Vehiculo *vehArr, int nVeh, Combustible *combArr, int nComb);
int buscarVehiculoPorID(Vehiculo *arr, int n, int id);
int buscarCombPorID(Combustible *arr, int n, int id);
void limpiarBuffer();

void main(void) {
    Vehiculo *vehiculos = NULL;
    Combustible *combustibles = NULL;
    int nVeh = 0, nComb = 0;
    int opcion;

    do {
        menu();
        if (scanf("%d", &opcion) != 1) {
            printf("Entrada invalida.\n");
            limpiarBuffer();
            continue;
        }
        limpiarBuffer();
        switch (opcion) {
            case 1: agregarVehiculo(&vehiculos, &nVeh); break;
            case 2: listarVehiculos(vehiculos, nVeh); break;
            case 3: modificarVehiculo(vehiculos, nVeh); break;
            case 4: agregarCombustible(&combustibles, &nComb); break;
            case 5: modificarCombustible(combustibles, nComb); break;
            case 6: listarCombustible(combustibles, nComb); break;
            case 7: calcularViaje(vehiculos, nVeh, combustibles, nComb); break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 0);

    free(vehiculos);
    free(combustibles);
    return 0;
}

void menu() {
    printf("\n=== SISTEMA CALCULO COSTO DE VIAJE ===\n");
    printf("1. Agregar Vehiculo\n");
    printf("2. Lista Vehiculo\n");
    printf("3. Modificar Vehiculo\n");
    printf("4. Agregar Combustible\n");
    printf("5. Modificar Combustible\n");
    printf("6. Lista Combustible\n");
    printf("7. Calcular Viaje\n");
    printf("0. Salir\n");
    printf("Elija una opcion: ");
}

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void agregarVehiculo(Vehiculo **arr, int *n) {
    Vehiculo v;
    v.id = (*n) + 1;

    printf("Marca: ");
    fgets(v.marca, sizeof(v.marca), stdin); v.marca[strcspn(v.marca, "\n")] = 0;
    printf("Modelo: ");
    fgets(v.modelo, sizeof(v.modelo), stdin); v.modelo[strcspn(v.modelo, "\n")] = 0;
    printf("Ano: ");
    scanf("%d", &v.ano); limpiarBuffer();
    printf("Placa: ");
    fgets(v.placa, sizeof(v.placa), stdin); v.placa[strcspn(v.placa, "\n")] = 0;
    printf("Consumo ciudad (L/100Km): ");
    scanf("%lf", &v.consumo_ciudad); limpiarBuffer();
    printf("Consumo carretera (L/100Km): ");
    scanf("%lf", &v.consumo_carretera); limpiarBuffer();
    printf("Costo seguro por ano: ");
    scanf("%lf", &v.costo_seguro_ano); limpiarBuffer();
    printf("Costo cambio por Km: ");
    scanf("%lf", &v.costo_cambio_por_km); limpiarBuffer();
    printf("Tiempo depreciacion (anos): ");
    scanf("%d", &v.tiempo_depreciacion_anos); limpiarBuffer();
    printf("Costo del vehiculo: ");
    scanf("%lf", &v.costo_vehiculo); limpiarBuffer();
    printf("Km promedio por ano: ");
    scanf("%lf", &v.km_promedio_ano); limpiarBuffer();
    printf("Costo limpieza por viaje: ");
    scanf("%lf", &v.costo_limpieza); limpiarBuffer();

    Vehiculo *tmp = realloc(*arr, ((*n) + 1) * sizeof(Vehiculo));
    if (!tmp) {
        printf("Error memoria.\n");
        return;
    }
    *arr = tmp;
    (*arr)[*n] = v;
    (*n)++;
    printf("Vehiculo agregado con ID %d\n", v.id);
}

void listarVehiculos(Vehiculo *arr, int n) {
    if (n == 0) {
        printf("No hay vehiculos registrados.\n");
        return;
    }
    for (int i = 0; i < n; ++i) {
        Vehiculo *v = &arr[i];
        printf("ID: %d | Marca: %s | Modelo: %s | Ano: %d | Placa: %s\n",
               v->id, v->marca, v->modelo, v->ano, v->placa);
        printf("  Consumo ciudad: %.3f | Consumo carretera: %.3f\n",
               v->consumo_ciudad, v->consumo_carretera);
        printf("  Costo seguro: %.2f | Costo cambio por km: %.4f\n",
               v->costo_seguro_ano, v->costo_cambio_por_km);
        printf("  Depreciacion anos: %d | Costo vehiculo: %.2f\n",
               v->tiempo_depreciacion_anos, v->costo_vehiculo);
        printf("  Km promedio: %.2f | Costo limpieza: %.2f\n",
               v->km_promedio_ano, v->costo_limpieza);
        printf("-----------------------------------\n");
    }
}

int buscarVehiculoPorID(Vehiculo *arr, int n, int id) {
    for (int i = 0; i < n; ++i) if (arr[i].id == id) return i;
    return -1;
}

void modificarVehiculo(Vehiculo *arr, int n) {
    if (n == 0) { printf("No hay vehiculos.\n"); return; }
    int id;
    printf("ID del vehiculo: ");
    if (scanf("%d", &id) != 1) { limpiarBuffer(); printf("Invalido.\n"); return; }
    limpiarBuffer();
    int idx = buscarVehiculoPorID(arr, n, id);
    if (idx == -1) { printf("No encontrado.\n"); return; }
    Vehiculo *v = &arr[idx];
    char linea[STRLEN];

    printf("Marca [%s]: ", v->marca);
    fgets(linea, sizeof(linea), stdin);
    if (linea[0] != '\n') { linea[strcspn(linea, "\n")] = 0; strncpy(v->marca, linea, sizeof(v->marca)); }

    printf("Modelo [%s]: ", v->modelo);
    fgets(linea, sizeof(linea), stdin);
    if (linea[0] != '\n') { linea[strcspn(linea, "\n")] = 0; strncpy(v->modelo, linea, sizeof(v->modelo)); }

    printf("Ano [%d]: ", v->ano);
    fgets(linea, sizeof(linea), stdin);
    if (linea[0] != '\n') { v->ano = atoi(linea); }

    printf("Consumo ciudad [%.3f]: ", v->consumo_ciudad);
    fgets(linea, sizeof(linea), stdin);
    if (linea[0] != '\n') { v->consumo_ciudad = atof(linea); }

    printf("Consumo carretera [%.3f]: ", v->consumo_carretera);
    fgets(linea, sizeof(linea), stdin);
    if (linea[0] != '\n') { v->consumo_carretera = atof(linea); }

    printf("Vehiculo modificado.\n");
}

void agregarCombustible(Combustible **arr, int *n) {
    Combustible c;
    c.id = (*n) + 1;
    printf("Nombre: ");
    fgets(c.nombre, sizeof(c.nombre), stdin); c.nombre[strcspn(c.nombre, "\n")] = 0;
    printf("Precio por litro: ");
    scanf("%lf", &c.precio_por_litro); limpiarBuffer();

    Combustible *tmp = realloc(*arr, ((*n) + 1) * sizeof(Combustible));
    if (!tmp) { printf("Error memoria.\n"); return; }
    *arr = tmp;
    (*arr)[*n] = c;
    (*n)++;
    printf("Combustible agregado con ID %d\n", c.id);
}

void listarCombustible(Combustible *arr, int n) {
    if (n == 0) { printf("No hay combustibles.\n"); return; }
    for (int i = 0; i < n; ++i) {
        printf("ID: %d | %s | Precio: %.3f\n", arr[i].id, arr[i].nombre, arr[i].precio_por_litro);
    }
}

int buscarCombPorID(Combustible *arr, int n, int id) {
    for (int i = 0; i < n; ++i) if (arr[i].id == id) return i;
    return -1;
}

void modificarCombustible(Combustible *arr, int n) {
    if (n == 0) { printf("No hay combustibles.\n"); return; }
    int id;
    printf("ID combustible: ");
    if (scanf("%d", &id) != 1) { limpiarBuffer(); printf("Invalido.\n"); return; }
    limpiarBuffer();
    int idx = buscarCombPorID(arr, n, id);
    if (idx == -1) { printf("No encontrado.\n"); return; }
    Combustible *c = &arr[idx];
    char linea[STRLEN];
    printf("Nombre [%s]: ", c->nombre);
    fgets(linea, sizeof(linea), stdin);
    if (linea[0] != '\n') { linea[strcspn(linea, "\n")] = 0; strncpy(c->nombre, linea, sizeof(c->nombre)); }

    printf("Precio por litro [%.3f]: ", c->precio_por_litro);
    fgets(linea, sizeof(linea), stdin);
    if (linea[0] != '\n') { c->precio_por_litro = atof(linea); }

    printf("Combustible modificado.\n");
}

void calcularViaje(Vehiculo *vehArr, int nVeh, Combustible *combArr, int nComb) {
    if (nVeh == 0 || nComb == 0) {
        printf("Debe agregar vehiculo y combustible.\n");
        return;
    }

    listarVehiculos(vehArr, nVeh);
    int idVeh;
    printf("ID vehiculo: ");
    scanf("%d", &idVeh); limpiarBuffer();
    int idxV = buscarVehiculoPorID(vehArr, nVeh, idVeh);
    if (idxV == -1) { printf("No encontrado.\n"); return; }
    Vehiculo *v = &vehArr[idxV];

    listarCombustible(combArr, nComb);
    int idComb;
    printf("ID combustible: ");
    scanf("%d", &idComb); limpiarBuffer();
    int idxC = buscarCombPorID(combArr, nComb, idComb);
    if (idxC == -1) { printf("No encontrado.\n"); return; }
    Combustible *c = &combArr[idxC];

    double kmTotales, pctCiudad;
    printf("KM totales: ");
    scanf("%lf", &kmTotales); limpiarBuffer();
    printf("Porcentaje ciudad (0-100): ");
    scanf("%lf", &pctCiudad); limpiarBuffer();
    if (pctCiudad < 0) pctCiudad = 0;
    if (pctCiudad > 100) pctCiudad = 100;

    double kmCiudad = kmTotales * (pctCiudad / 100.0);
    double kmCarretera = kmTotales - kmCiudad;

    double litrosCiudad = (v->consumo_ciudad * kmCiudad) / 100.0;
    double litrosCarretera = (v->consumo_carretera * kmCarretera) / 100.0;
    double litrosTotales = litrosCiudad + litrosCarretera;
    double costoComb = litrosTotales * c->precio_por_litro;

    double costoSeguro = (v->km_promedio_ano > 0) ? (v->costo_seguro_ano / v->km_promedio_ano) * kmTotales : 0;
    double depViaje = 0;
    if (v->tiempo_depreciacion_anos > 0 && v->km_promedio_ano > 0) {
        double depAnual = v->costo_vehiculo / v->tiempo_depreciacion_anos;
        depViaje = (depAnual / v->km_promedio_ano) * kmTotales;
    }

    double costoMant = v->costo_cambio_por_km * kmTotales;
    double costoTotal = costoComb + costoSeguro + depViaje + costoMant + v->costo_limpieza;
    double costoKm = (kmTotales > 0) ? costoTotal / kmTotales : 0;

    printf("\n--- RESULTADO ---\n");
    printf("Vehiculo: %s %s\n", v->marca, v->modelo);
    printf("Combustible: %s\n", c->nombre);
    printf("KM: %.2f | Ciudad: %.2f | Carretera: %.2f\n", kmTotales, kmCiudad, kmCarretera);
    printf("Costo combustible: %.2f\n", costoComb);
    printf("Costo seguro: %.2f\n", costoSeguro);
    printf("Depreciacion: %.2f\n", depViaje);
    printf("Mantenimiento: %.2f\n", costoMant);
    printf("Limpieza: %.2f\n", v->costo_limpieza);
    printf("Costo total: %.2f\n", costoTotal);
    printf("Costo por km: %.4f\n", costoKm);
}
