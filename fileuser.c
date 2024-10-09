#include <stdio.h>
#include <stdlib.h>

void open_file(FILE** ptr, char filename[], char mode[]){
    *ptr = fopen(filename, mode);
    if (*ptr == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", filename);
        exit(1);
    }
}

void close_file(FILE* ptr){
    fclose(ptr);
}

long get_size_file(FILE* f){
    fseek(f, 0, SEEK_END); // seek to end of file
    long size = ftell(f); // get current file pointer
    fseek(f, 0, SEEK_SET); // seek back to start
    return(size);
}

int* read_data(FILE *fptr){
    long c = get_size_file(fptr) / sizeof(int); // Divisé par sizeof(int) pour lire le nombre d'entiers
    int *arrptr = (int*)malloc(c * sizeof(int));
    if (arrptr == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return NULL;
    }
    
    fread(arrptr, sizeof(int), c, fptr); // Lire les données directement dans arrptr
    
    for (int i = 0; i < c; i++) {
        printf("%d\n", *(arrptr + i));
    }   
    fseek(fptr, 0, SEEK_SET); // Remet le curseur au début du fichier
    return arrptr;
}

void write_data(FILE* ptr, int data[], int l){
    fwrite(data, sizeof(int), l, ptr);
}

void read_hex(FILE *fptr){
    unsigned char* arrptr = (unsigned char*)malloc(258 * sizeof(char));
    if (arrptr == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return;
    }
    while (fread(arrptr, sizeof(char), 258, fptr) > 0) {
        for (int i = 0; i < 258; i++) {
            printf("%#010x ", *(arrptr + i));
            if (i % 6 == 0) {
                printf("\n");
            }
        }
    }
    free(arrptr);
    fseek(fptr, 0, SEEK_SET);
}

void read_text(FILE* ptr){
    long c = get_size_file(ptr);
    char *arrptr = (char*)malloc((c + 1) * sizeof(char)); // +1 pour le caractère nul
    if (arrptr == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return;
    }
    fread(arrptr, sizeof(char), c, ptr);
    arrptr[c] = '\0'; // Ajoute le caractère de fin de chaîne
    printf("%s\n", arrptr);
    free(arrptr);
    fseek(ptr, 0, SEEK_SET);
}

void write_text(FILE* ptr){
    char* p = (char*)malloc(100 * sizeof(char));
    if (p == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return;
    }
    scanf(" %[^\n]", p);  // Lire une ligne complète avec des espaces
    fprintf(ptr, "%s", p);  // Utiliser "%s" pour écrire le texte correctement
    free(p);
}

int main(int argc, char* argv[]){
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char* i = argv[1];
    char n;
    FILE *ptr = NULL;
    int tr = 1;
    int cont;

    printf("modificateur de fichier\nfichier chargé : %s\n", i);
    printf("Que voulez-vous faire avec? s pour obtenir la taille; h pour l'afficher en hexa; r pour le lire; w pour écrire; b pour écrire en binaire; v pour récupérer les valeurs; q pour quitter\n");
    
    while (tr) {
        printf("\nVotre choix : ");
        scanf(" %c", &n); // Ajoutez un espace avant %c pour consommer tout caractère de saut de ligne résiduel
        switch (n) {
        case 's':
            open_file(&ptr, i, "rb");
            printf("Taille du fichier: %ld octets\n", get_size_file(ptr));
            close_file(ptr);
            break;
        case 'h':
            open_file(&ptr, i, "rb");
            read_hex(ptr);
            close_file(ptr);
            break;
        case 'r':
            open_file(&ptr, i, "r");
            read_text(ptr);
            close_file(ptr);
            break;
        case 'w':
            open_file(&ptr, i, "a");
            printf("Entrez le texte à écrire:\n");
            write_text(ptr);
            close_file(ptr);
            break;
        case 'b':
            printf("Combien de valeurs voulez-vous ajouter?\n");
            scanf("%d", &cont);
            printf("Entrez les valeurs une par une:\n");
            int* leptr = (int*)malloc(cont * sizeof(int));
            if (leptr == NULL) {
                printf("Erreur d'allocation mémoire\n");
                break;
            }
            for (int y = 0; y < cont; y++) {
                scanf("%d", &leptr[y]);
            }
            open_file(&ptr, i, "ab");
            write_data(ptr, leptr, cont);
            close_file(ptr);
            free(leptr);
            break;
        case 'v':
            open_file(&ptr, i, "rb");
            read_data(ptr);
            close_file(ptr);
            break;
        case 'q':
            tr = 0;
            break;
        default:
            printf("Option inconnue\n");
            break;
        }
    }

    return 0;
}