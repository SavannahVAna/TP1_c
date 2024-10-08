#include <stdio.h>
#include <stdlib.h>

void open_file(FILE* ptr, char filename[], char mode[]){
    ptr = fopen(filename, mode);
}

void close_file(FILE* ptr){
    fclose(ptr);
}

long get_size_file(FILE* f){
    fseek(f, 0, SEEK_END); // seek to end of file
    long size = ftell(f); // get current file pointer
    fseek(f, 0, SEEK_SET);
    return(size);
}

int* read_data(FILE *fptr){
    long c = get_size_file(fptr);
    int *arrptr = (int*)malloc(c* sizeof(int));
    
    for (int i = 0; i < c; i++)
    {
        printf("%d", (*arrptr +i));
    }   
    free(arrptr);
    fseek(fptr, 0, SEEK_SET);
}

void write_data(FILE* ptr, int data[], int l){
    fwrite(data, sizeof(int), l,ptr);
}

void read_hex(FILE *fptr){
 
    unsigned char* arrptr; 
    arrptr = (unsigned char*)malloc(258* sizeof(char));
    while (fread(arrptr, sizeof(char), 258, fptr) > 0)
    {
        for (int i =0 ; i< 258; i++){
            printf("%#010x ", *(arrptr+i));
            if(i%6==0){
                printf("\n");
            }
        }
    }
    free(arrptr);
    fseek(fptr, 0, SEEK_SET);
}

void read_text(FILE* ptr){
    long c = get_size_file(ptr);
    char *arrptr = (char*)malloc(c* sizeof(char));
    fgets(*arrptr, c, ptr);
    printf("%s", ptr);
    free(arrptr);
    fseek(ptr, 0, SEEK_SET);
}

void write_text(FILE* ptr){
    char* p = (char*)malloc(100);
    scanf("%s",p);
    fprintf(ptr, p);
}

void main(int argc, char* argv[]){
    char i = argv[1];
    char n;
    FILE *ptr;
    int tr = 1;
    printf("modificateur de fichier\nfichier chargé : " + i);
    printf("\nque voulez vous faire avec? s to get the size ; h pour l\'afficher en hexa ; r pour le lire ; w pour write ; b pour ecrire en binaire ; r pour recupérer les valeurs ; q pour quitter\n");
    while (tr)
    {
        scanf("%c", &n);
        switch (n)
        {
        case 's':
            open_file(ptr, i, 'rb');
            printf(get_size_file(ptr));
            close_file(ptr);
            break;
        case 'h':
            open_file(ptr, i, 'rb');
            read_hex(ptr);
            close_file;
            break;
        case 'r':
            open_file(ptr,i, 'r');
            read_text(ptr);
            close_file(ptr);
            break;
        case 'w':
            open_file(ptr, i , 'a');
            printf("entrez le texte a ecrire\n");
            write_text(ptr);
            close_file(ptr);
            break;
        case 'b':
            
        default:
            break;
        }
    }
    
}