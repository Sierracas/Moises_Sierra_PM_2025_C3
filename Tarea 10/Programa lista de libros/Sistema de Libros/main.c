#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct libro {
    char ano[10];
    char autor[50];
    char titulo[50];
    char descripcion[100];
    float precio;
    int codigo;
    struct libro *sig;
} Libro;

void leer_texto(char *cad, int tam) {
    fgets(cad, tam, stdin);
    cad[strcspn(cad, "\n")] = 0;
}

Libro* crear_libro() {
    char temp[50];
    Libro *nuevo = (Libro*)malloc(sizeof(Libro));

    printf("Ano: ");
    leer_texto(nuevo->ano, 10);

    printf("Autor: ");
    leer_texto(nuevo->autor, 50);

    printf("Titulo: ");
    leer_texto(nuevo->titulo, 50);

    printf("Descripcion: ");
    leer_texto(nuevo->descripcion, 100);

    printf("Precio: ");
    leer_texto(temp, 50);
    nuevo->precio = atof(temp);

    printf("Codigo: ");
    leer_texto(temp, 50);
    nuevo->codigo = atoi(temp);

    nuevo->sig = NULL;
    return nuevo;
}

void agregar_libro(Libro **head) {
    Libro *nuevo = crear_libro();
    if (*head == NULL) {
        *head = nuevo;
        return;
    }
    Libro *tmp = *head;
    while (tmp->sig != NULL) tmp = tmp->sig;
    tmp->sig = nuevo;
}

void listar_libros(Libro *head) {
    int n = 1;
    while (head != NULL) {
        printf("%d\n", n);
        printf("Ano: %s\n", head->ano);
        printf("Autor: %s\n", head->autor);
        printf("Titulo: %s\n", head->titulo);
        printf("Descripcion: %s\n", head->descripcion);
        printf("Precio: %.2f\n", head->precio);
        printf("Codigo: %d\n", head->codigo);
        printf("----------------------------------------------------------------------------------------------\n");
        head = head->sig;
        n++;
    }
}

void buscar_autor(Libro *head) {
    char autor[50];
    printf("Autor a buscar: ");
    leer_texto(autor, 50);
    while (head != NULL) {
        if (strcmp(head->autor, autor) == 0) {
            printf("Ano: %s\n", head->ano);
            printf("Autor: %s\n", head->autor);
            printf("Titulo: %s\n", head->titulo);
            printf("Descripcion: %s\n", head->descripcion);
            printf("Precio: %.2f\n", head->precio);
            printf("Codigo: %d\n", head->codigo);
            printf("-----------------------------\n");
        }
        head = head->sig;
    }
}

void editar_libro(Libro *head) {
    char temp[50];
    int codigo;
    printf("Codigo a editar: ");
    leer_texto(temp, 50);
    codigo = atoi(temp);

    while (head != NULL) {
        if (head->codigo == codigo) {
            printf("Nuevo ano: ");
            leer_texto(head->ano, 10);

            printf("Nuevo autor: ");
            leer_texto(head->autor, 50);

            printf("Nuevo titulo: ");
            leer_texto(head->titulo, 50);

            printf("Nueva descripcion: ");
            leer_texto(head->descripcion, 100);

            printf("Nuevo precio: ");
            leer_texto(temp, 50);
            head->precio = atof(temp);

            printf("Nuevo codigo: ");
            leer_texto(temp, 50);
            head->codigo = atoi(temp);

            return;
        }
        head = head->sig;
    }
}

void eliminar_libro(Libro **head) {
    char temp[50];
    int codigo;
    printf("Codigo a eliminar: ");
    leer_texto(temp, 50);
    codigo = atoi(temp);

    Libro *act = *head, *ant = NULL;

    while (act != NULL) {
        if (act->codigo == codigo) {
            if (ant == NULL) {
                *head = act->sig;
            } else {
                ant->sig = act->sig;
            }
            free(act);
            return;
        }
        ant = act;
        act = act->sig;
    }
}

void ordenar_precio(Libro **head) {
    if (*head == NULL) return;

    int cambio;
    Libro *i, *j;
    Libro *fin = NULL;

    do {
        cambio = 0;
        i = *head;

        while (i->sig != fin) {
            j = i->sig;
            if (i->precio > j->precio) {
                Libro tmp = *i;

                strcpy(i->ano, j->ano);
                strcpy(i->autor, j->autor);
                strcpy(i->titulo, j->titulo);
                strcpy(i->descripcion, j->descripcion);
                i->precio = j->precio;
                i->codigo = j->codigo;

                strcpy(j->ano, tmp.ano);
                strcpy(j->autor, tmp.autor);
                strcpy(j->titulo, tmp.titulo);
                strcpy(j->descripcion, tmp.descripcion);
                j->precio = tmp.precio;
                j->codigo = tmp.codigo;

                cambio = 1;
            }
            i = i->sig;
        }
        fin = i;
    } while (cambio);
}

void guardar_archivo(Libro *head) {
    FILE *f = fopen("libros.txt", "w");
    if (!f) return;

    while (head != NULL) {
        fprintf(f, "%s|%s|%s|%s|%.2f|%d\n",
            head->ano,
            head->autor,
            head->titulo,
            head->descripcion,
            head->precio,
            head->codigo
        );
        head = head->sig;
    }

    fclose(f);
}

Libro* cargar_archivo() {
    FILE *f = fopen("libros.txt", "r");
    if (!f) return NULL;

    Libro *head = NULL;
    Libro *ultimo = NULL;

    char linea[300];
    while (fgets(linea, sizeof(linea), f)) {
        Libro *n = (Libro*)malloc(sizeof(Libro));

        sscanf(linea, "%9[^|]|%49[^|]|%49[^|]|%99[^|]|%f|%d",
            n->ano, n->autor, n->titulo, n->descripcion,
            &n->precio, &n->codigo);

        n->sig = NULL;

        if (head == NULL) {
            head = n;
            ultimo = n;
        } else {
            ultimo->sig = n;
            ultimo = n;
        }
    }

    fclose(f);
    return head;
}

int main() {
    Libro *head = cargar_archivo();
    char temp[10];
    int op;

    while (1) {
        printf("1 Agregar libro\n");
        printf("2 Listar libros\n");
        printf("3 Editar libro\n");
        printf("4 Eliminar libro\n");
        printf("5 Buscar por autor\n");
        printf("6 Ordenar por precio\n");
        printf("7 Guardar y salir\n");
        printf("8 Salir sin guardar\n");
        printf("Opcion: ");

        leer_texto(temp, 10);
        op = atoi(temp);

        if (op == 1) agregar_libro(&head);
        else if (op == 2) listar_libros(head);
        else if (op == 3) editar_libro(head);
        else if (op == 4) eliminar_libro(&head);
        else if (op == 5) buscar_autor(head);
        else if (op == 6) ordenar_precio(&head);
        else if (op == 7) {
            guardar_archivo(head);
            break;
        }
        else if (op == 8) break;
    }
    return 0;
}
