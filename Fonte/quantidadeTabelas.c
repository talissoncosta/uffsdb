//BufferPool
#include "buffend.h"

int quantidadeTabelas(){

    FILE *dicionario;
    int codTbl = 0;

    char directory[LEN_DB_NAME*2];
    strcpy(directory, connected.db_directory);
    strcat(directory, "fs_object.dat");

    if((dicionario = fopen(directory,"a+b")) == NULL)
        return ERRO_ABRIR_ARQUIVO;

    while(fgetc (dicionario) != EOF){
        fseek(dicionario, -1, 1);

        codTbl++; // Conta quantas vezes é lido uma tupla no dicionario.

        fseek(dicionario, 48, 1);
    }

    fclose(dicionario);

    return codTbl;
}