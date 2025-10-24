#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char calle[20];
    int numero;
    int cp;
    char localidad[20];
} domicilio;

struct empleado

{
    char nombre[20];
    char departamento[20];
    float sueldo;
        dimicilio direccion;
};

void Lectura(struct empleado *a)
{
    printf("\nIngrese el nombre de del empleado: ");
    gets(a->nombre);
    fflush(stdin);
    printf("Ingrese el departamento de la empresa: ");
    gtes(a->departamento);
    printf("Ingrese el sueldo del empleado: ");
    scanf("%f", &a->sueldo);
    fflush(stdin);
    printf("--Ingrese la direccion del empleado--");
    printf("\n\tCalle: ");
    gets(a->direccion.calle);
    printf("\tNumero: ");
    scanf("%d", &a->direccion.numero);
    printf("\tCodigo Postal: ");
    scanf("%d", &a->direccion.cp);
    fflush(stdin);
    printf("\tLocalidad: ");
    gets(a-> direccion.localidad);
}

void main(void)
{

}
