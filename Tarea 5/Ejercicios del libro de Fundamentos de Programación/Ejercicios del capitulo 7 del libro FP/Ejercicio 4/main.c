#include <stdio.h>
#include <stdlib.h>

void main(void)
{
char *cad0;
cad0 = "Argentina";
puts(cad0);

cad0 = "Brasil";
puts(cad0);

char *cad1[50];
printf("Ingrese una cadena: ");
fgets(*cad1, sizeof(cad1), stdin);   gets(cad1);
puts(cad1);

char cad2[20] = "Mexico";
puts(cad2);

printf("Ingrese otra cadena: ");
fgets(cad2, sizeof(cad2), stdin);
puts(cad2);

strncpy(cad2, "Guatemala", sizeof(cad2) - 1);
cad2[sizeof(cad2) - 1] = '\0';
puts(cad2);

return 0;
}
