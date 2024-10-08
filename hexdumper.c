#include <stdio.h>
#include <stdlib.h>

void main(int argc, char* argv[]){
 
    FILE *fptr;
    fptr = fopen(argv[1], "rb");
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
    fclose(fptr);
    free(arrptr);
    
}