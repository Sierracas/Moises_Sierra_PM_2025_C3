#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longitud(char *cadena);

void main(void)
{
int i, n, l = -1, p = 0, t;
char cadena[50], FRA[20][50];
printf("\nIngrese el numero de filas del arreglo: ");
scanf("%d", &n);
for (i=0; i<n; i++)
{
    printf("Ingrese la linea %d de texto. Maximo 50 caracteres: ", i+1);
    fflush(stdin);
    gets(FRA[i]);
}
printf("\n");
for (i=0; i<n; i++)
{
    strcpy(cadena, FRA[i]);
    t = longitud (cadena);
    if (t > l)
    {
        l = t;
        p = i;
    }
}
printf("\nLa cadena con mayor longitud es: ");
puts(FRA[p]);
printf("\nLongitud: %d", l);

return 0;
}

int longitud(char *cadena)

{
    int cue = 0;
    while (cadena[cue] != '\0')
        cue++;
    return (cue);
}
