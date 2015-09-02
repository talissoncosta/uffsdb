//BufferPool
#include "buffend.h"

struct fs_objects leObjeto(char *nTabela){

    FILE *dicionario;
    char *tupla = (char *)malloc(sizeof(char)*TAMANHO_NOME_TABELA);
    memset(tupla, '\0', TAMANHO_NOME_TABELA);
    int cod;

    char directory[LEN_DB_NAME*2];
    strcpy(directory, connected.db_directory);
    strcat(directory, "fs_object.dat");

    dicionario = fopen(directory, "a+b"); // Abre o dicionario de dados.

    struct fs_objects objeto;

    if(!verificaNomeTabela(nTabela)){
        printf("ERROR: relation \"%s\" was not found.\n", nTabela);
        if (dicionario)
            fclose(dicionario);
        free(tupla);

        return objeto;
    }

    if (dicionario == NULL) {
        printf("ERROR: data dictionary was not found.\n\n");
        free(tupla);
        return objeto;
    }


    while(fgetc (dicionario) != EOF){
        fseek(dicionario, -1, 1);

        fread(tupla, sizeof(char), TAMANHO_NOME_TABELA , dicionario); //Lê somente o nome da tabela

        if(objcmp(tupla, nTabela) == 0){ // Verifica se o nome dado pelo usuario existe no dicionario de dados.
            strcpylower(objeto.nome, tupla);
            fread(&cod,sizeof(int),1,dicionario);   // Copia valores referentes a tabela pesquisada para a estrutura.
            objeto.cod=cod;
            fread(tupla,sizeof(char),TAMANHO_NOME_TABELA,dicionario);
            strcpylower(objeto.nArquivo, tupla);
            fread(&cod,sizeof(int),1,dicionario);
            objeto.qtdCampos = cod;

            free(tupla);
            fclose(dicionario);
            return objeto;
        }
        fseek(dicionario, 28, 1); // Pula a quantidade de caracteres para a proxima verificacao(4B do codigo, 20B do nome do arquivo e 4B da quantidade de campos).
    }
    free(tupla);
    fclose(dicionario);

    return objeto;
}
