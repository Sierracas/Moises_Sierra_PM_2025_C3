#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main(void)
{
float RAD, ALT, VOL, ARE;
printf("Ingrese el radio y la altura del cilindro: ");
scanf("%F %f", &RAD, &ALT);
VOL = M_PI * pow (RAD, 2) * ALT;
ARE = 2 * M_PI * RAD * ALT;
printf("\nEl volumen es: %6.2f  \t El área es: %6,2f", VOL, ARE);
}
