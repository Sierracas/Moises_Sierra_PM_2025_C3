#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(void)
{
int i;
double d;
long l;
char cad0[50], *cad1;

printf("\nIngrese una cadena de caracteres: ");
fgets(cad0, sizeof(cad0), stdin);
cad0[strcspn(cad0, "\n")] = '\0';

i = atoi(cad0);
printf("\n%s \t %d", cad0, i+3);

printf("\nIngrese una cadena de cacacteres: ");
fgets(cad0, sizeof(cad0), stdin);
cad0[strcspn(cad0, "\n")] = '\0';

d = atof(cad0);
printf("\n%s \t %.21f", cad0, d + 1.50);

d = strtod(cad0, &cad1);
printf("\n%s, \t %.21f", cad0, d+1.50);
if (*cad1 != '\0') puts(cad1);

l = atol(cad0);
printf("\n%s \t %1d ", cad0, 1+10);

l = strtol(cad0, &cad1, 10);
printf("\n%s \t %1d", cad0, 1+10);
if (*cad1 != '\0') puts(cad1);

return 0;
}
