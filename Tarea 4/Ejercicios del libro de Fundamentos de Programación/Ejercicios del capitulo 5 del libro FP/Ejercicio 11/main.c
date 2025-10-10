#include <stdio.h>
#include <stdlib.h>

const MAX=100;

void Lectura(int[], int);
int Binaria(int *, int, int);

void main(void)
{
    int RES, ELE, TAM, VEC[MAX];
    do
    {
        printf("Ingrese el tamano del arreglo: ");
        scanf("%d", &TAM);
    }
    while (TAM>MAX|| TAM<1);

    Lectura(VEC, TAM);
    printf("\nIngrese el elemento a Buscar: ");
    scanf("%d", &ELE);
    RES = Binaria(VEC, TAM, ELE);

    if (RES)
        printf("\nEl elemento se encuentra en la posición: %d", RES);
        else
        printf("\nEl elemento encuentra no se encuentra en el arreglo");
}

void Lectura(int A[], int T)
{
    int I;
    for (I=0; I<T; I++)
    {
        printf("Ingrese el elemento &d: ", I+1);
    }
}

int Binaria(int A[], int T, int E)
{
    int ELE, IZQ = 0, CEN, DER = T-1, BAN = 0;
    while ((IZQ <= DER) && (!BAN))
    {
        CEN = (IZQ + DER) / 2;
        if (E == A[CEN])
            BAN = CEN;
        else
            if (E > A[CEN])
            IZQ = CEN + 1;
        else
            DER = CEN - 1;
    }
    return (BAN);
}
