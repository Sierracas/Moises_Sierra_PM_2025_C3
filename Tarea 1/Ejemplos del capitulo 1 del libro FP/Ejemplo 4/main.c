#include <stdio.h>
#include <stdlib.h>

void main(void)
{
float BAS, ALT, SUP;
printf("Ingrese la base y la altura del tri�ngulo: ");
scanf("%F %f", &BAS, &ALT);
SUP = BAS * ALT / 2;
printf("\nLa superficie del tri�ngulo es: %5.2f", SUP);
}
