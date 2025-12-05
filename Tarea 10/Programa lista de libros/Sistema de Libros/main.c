#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Libro {
    int ano;
    char autor[50];
    char titulo[50];
    char descripcion[150];
    float precio;
    int codigo;
    struct Libro *next;
} Libro;

void limpiar() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void leer_texto(char *buffer, int tam) {
    fgets(buffer, tam, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
}

Libro* agregar_libro(Libro *head) {
    Libro *n = (Libro*)malloc(sizeof(Libro));
    if (!n) return head;

    printf("Ano: ");
    scanf("%d", &n->ano);
    limpiar();

    printf("Autor: ");
    leer_texto(n->autor, 50);

    printf("Titulo: ");
    leer_texto(n->titulo, 50);

    printf("Descripcion: ");
    leer_texto(n->descripcion, 150);

    printf("Precio: ");
    scanf("%f", &n->precio);
    limpiar();

    printf("Codigo: ");
    scanf("%d", &n->codigo);
    limpiar();

    n->next = head;
    return n;
}

void mostrar(Libro *p) {
    printf("\n--- Libro ---\n");
    printf("Ano: %d\n", p->ano);
    printf("Autor: %s\n", p->autor);
    printf("Titulo: %s\n", p->titulo);
    printf("Descripcion: %s\n", p->descripcion);
    printf("Precio: %.2f\n", p->precio);
    printf("Codigo: %d\n", p->codigo);
}

void guardar_archivo(Libro *head) {
    FILE *f = fopen("libros.txt", "w");
    if (!f) return;

    Libro *p = head;
    while (p) {
        fprintf(f, "%d|%s|%s|%s|%f|%d\n",
                p->ano, p->autor, p->titulo,
                p->descripcion, p->precio, p->codigo);
        p = p->next;
    }
    fclose(f);
}

Libro* cargar_archivo() {
    FILE *f = fopen("libros.txt", "r");
    if (!f) return NULL;

    Libro *head = NULL;

    while (1) {
        Libro temp;
        char linea[300];

        if (!fgets(linea, sizeof(linea), f)) break;

        if (sscanf(linea, "%d|%49[^|]|%49[^|]|%149[^|]|%f|%d",
                   &temp.ano, temp.autor, temp.titulo,
                   temp.descripcion, &temp.precio, &temp.codigo) != 6)
            continue;

        Libro *n = (Libro*)malloc(sizeof(Libro));
        *n = temp;
        n->next = head;
        head = n;
    }

    fclose(f);
    return head;
}

void buscar(Libro *head) {
    int op;
    char texto[50];

    printf("Buscar por: 1) titulo 2) autor: ");
    scanf("%d", &op);
    limpiar();

    printf("Texto: ");
    leer_texto(texto, 50);

    Libro *p = head;
    int encontrado = 0;

    while (p) {
        if ((op == 1 && strcmp(p->titulo, texto) == 0) ||
            (op == 2 && strcmp(p->autor, texto) == 0)) {
            mostrar(p);
            encontrado = 1;
        }
        p = p->next;
    }

    if (!encontrado) {
        printf("\nNo encontrado.\n");
    }
}

void listar(Libro *head) {
    Libro *p = head;
    while (p) {
        mostrar(p);
        p = p->next;
    }
}

void main(void) {
    Libro *head = NULL;
    int op;

    head = cargar_archivo();

    do {
        printf("\nMenu\n");
        printf("1. Agregar libro\n");
        printf("2. Buscar libro\n");
        printf("3. Listar libros\n");
        printf("4. Guardar y salir\n");
        printf("Opcion: ");
        scanf("%d", &op);
        limpiar();

        switch (op) {
            case 1:
                head = agregar_libro(head);
                break;
            case 2:
                buscar(head);
                break;
            case 3:
                listar(head);
                break;
            case 4:
                guardar_archivo(head);
                printf("Guardado.\n");
                break;
        }

    } while (op != 4);

    return 0;
}
