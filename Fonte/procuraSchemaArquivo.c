//BufferPool
#include "buffend.h"

/* ----------------------------------------------------------------------------------------------
    Objetivo:   Copia todas as informações menos a tabela do objeto, que será removida.
    Parametros: Objeto que será removido do schema.
    Retorno:    INT
                SUCCESS,
                ERRO_REMOVER_ARQUIVO_SCHEMA
   ---------------------------------------------------------------------------------------------*/

int procuraSchemaArquivo(struct fs_objects objeto){

    FILE *schema, *newSchema;
    int cod = 0;
    char *tupla = (char *)malloc(sizeof(char) * 109);
    memset(tupla, '\0', 109);

    tp_table *esquema = (tp_table *)malloc(sizeof(tp_table)*objeto.qtdCampos);
    memset(esquema, 0, sizeof(tp_table)*objeto.qtdCampos);

    char directory[LEN_DB_NAME*2];
    memset(&directory, '\0', LEN_DB_NAME*2);

    strcpy(directory, connected.db_directory);
    strcat(directory, "fs_schema.dat");

    if((schema = fopen(directory, "a+b")) == NULL) {
        free(tupla);
        return ERRO_REMOVER_ARQUIVO_SCHEMA;
    }

    strcpy(directory, connected.db_directory);
    strcat(directory, "fs_nschema.dat");

    if((newSchema = fopen(directory, "a+b")) == NULL) {
        free(tupla);
        return ERRO_REMOVER_ARQUIVO_SCHEMA;
    }

    fseek(newSchema, 0, SEEK_SET);

    while((fgetc (schema) != EOF)){ // Varre o arquivo ate encontrar todos os campos com o codigo da tabela.
        fseek(schema, -1, 1);
        fseek(newSchema, 0, SEEK_END);

        if(fread(&cod, sizeof(int), 1, schema)){ // Le o codigo da tabela.
            if(cod != objeto.cod){
                fwrite(&cod, sizeof(int), 1, newSchema);

                fread(tupla, sizeof(char), TAMANHO_NOME_CAMPO, schema);
                strcpylower(esquema[0].nome,tupla);                  // Copia dados do campo para o esquema.
                fwrite(tupla, sizeof(char), TAMANHO_NOME_CAMPO, newSchema);

                fread(&esquema[0].tipo , sizeof(char), 1 , schema);
                fread(&esquema[0].tam  , sizeof(int) , 1 , schema);
                fread(&esquema[0].chave, sizeof(int) , 1 , schema);

                fwrite(&esquema[0].tipo , sizeof(char), 1, newSchema);
                fwrite(&esquema[0].tam  , sizeof(int) , 1, newSchema);
                fwrite(&esquema[0].chave, sizeof(int) , 1, newSchema);

                fread(tupla, sizeof(char), TAMANHO_NOME_TABELA, schema);
                strcpylower(esquema[0].tabelaApt,tupla);
                fwrite(&esquema[0].tabelaApt, sizeof(char), TAMANHO_NOME_TABELA, newSchema);

                fread(tupla, sizeof(char), TAMANHO_NOME_CAMPO, schema);
                strcpylower(esquema[0].attApt,tupla);
                fwrite(&esquema[0].attApt, sizeof(char), TAMANHO_NOME_CAMPO, newSchema);

            } else {
                fseek(schema, 109, 1);
            }
        }
    }

    fclose(newSchema);
    fclose(schema);

    char directoryex[LEN_DB_NAME*4];
    memset(&directoryex, '\0', LEN_DB_NAME*4);
    strcpy(directoryex, connected.db_directory);
    strcat(directoryex, "fs_schema.dat");

    remove(directoryex);

    strcpy(directoryex, "mv ");
    strcat(directoryex, connected.db_directory);
    strcat(directoryex, "fs_nschema.dat ");
    strcat(directoryex, connected.db_directory);
    strcat(directoryex, "fs_schema.dat");

    system(directoryex);

    free(tupla);
    return SUCCESS;
}