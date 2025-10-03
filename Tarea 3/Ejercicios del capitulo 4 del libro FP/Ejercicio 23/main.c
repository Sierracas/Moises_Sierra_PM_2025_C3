#include <stdio.h>
#include <stdlib.h>

void trueque(int *x, int *y)
{
int tem;
tem = *x;
*x = *y;
*y = tem;
}

int suma(int x)
{
 return (x + x);
}

void main(void)
{
    int a = 5, b = 10;

    printf("Antes del trueque: a = %d, b = %d\n", a, b);
    trueque(&a, &b);
    printf("Despues del trueque: a = %d, b = %d\n", a, b);

    int r = suma(7);
    printf("La suma doble de 7 es: %d\n", r);

    return 0;
}
