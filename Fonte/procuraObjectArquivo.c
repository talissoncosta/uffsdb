//BufferPool
#include "buffend.h"

/* ----------------------------------------------------------------------------------------------
    Objetivo:   Copia todas as informações menos a tabela com nome NomeTabela, que será removida.
    Parametros: Nome da tabela que será removida do object.dat.
    Retorno:    INT
                SUCCESS,
                ERRO_ABRIR_ARQUIVO
   ---------------------------------------------------------------------------------------------*/

int procuraObjectArquivo(char *nomeTabela){
    int teste        = 0,
        cont         = 0,
        achou        = 0,
        tamanhoTotal = sizeof(struct fs_objects);

    char *table = (char *)malloc(sizeof(char) * tamanhoTotal);
    FILE *dicionario, *fp;

    char directory[LEN_DB_NAME*2];
    strcpy(directory, connected.db_directory);
    strcat(directory, "fs_object.dat");

    if((dicionario = fopen(directory,"a+b")) == NULL) {
        free(table);
        return ERRO_ABRIR_ARQUIVO;
    }

    strcpy(directory, connected.db_directory);
    strcat(directory, "fs_nobject.dat");

    if((fp = fopen(directory, "a+b")) == NULL) {
        free(table);
        return ERRO_ABRIR_ARQUIVO;
    }

    fseek(dicionario, 0, SEEK_SET);
    fseek(fp, 0, SEEK_SET);

    while(cont < quantidadeTabelas()){
        fread(table, sizeof(char), tamanhoTotal, dicionario);
        teste = TrocaArquivosObj(nomeTabela, table);

        if(teste == 0){                                         //NÃO É IGUAL
            fseek(fp, 0, SEEK_END);
            fwrite(table, sizeof(char), tamanhoTotal, fp);
        } else if(achou != 1){                                    //É IGUAL E NÃO TINHA SIDO DESCOBERTO.
            achou = 1;
            fread(table, sizeof(char), 0, dicionario);
        }
        cont++;
    }

    fclose(fp);
    fclose(dicionario);

    char directoryex[LEN_DB_NAME*4];
    strcpy(directoryex, connected.db_directory);
    strcat(directoryex, "fs_object.dat");

    remove(directoryex);

    strcpy(directoryex, "mv ");
    strcat(directoryex, connected.db_directory);
    strcat(directoryex, "fs_nobject.dat ");
    strcat(directoryex, connected.db_directory);
    strcat(directoryex, "fs_object.dat");

    system(directoryex);

    free(table);
    return SUCCESS;
}