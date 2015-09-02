//BufferPool
#include "buffend.h"

/* ----------------------------------------------------------------------------------------------
    Objetivo:   Verificação de existência de um arquivo.
    Parametros: Nome do arquivo.
    Retorno:    INT 1 (existe) , 0 (não existe).
   ---------------------------------------------------------------------------------------------*/

int existeArquivo(const char* filename){

    char directory[LEN_DB_NAME*2];
    strcpy(directory, connected.db_directory);
    strcat(directory, filename);
    FILE* fptr = fopen(directory, "r");

    if (fptr != NULL){
        fclose(fptr);

        return 1;
    }

    return 0;
}