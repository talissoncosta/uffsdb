//BufferPool
#include "buffend.h"

// LEITURA DE DICIONARIO E ESQUEMA
tp_table *leSchema (struct fs_objects objeto){
    FILE *schema;
    int i = 0, cod = 0;
    char *tupla = (char *)malloc(sizeof(char)*TAMANHO_NOME_CAMPO);
    memset(tupla, 0, TAMANHO_NOME_CAMPO);
    char *tuplaT = (char *)malloc(sizeof(char)*TAMANHO_NOME_TABELA+1);
    memset(tuplaT, 0, TAMANHO_NOME_TABELA+1);

    tp_table *esquema = (tp_table *)malloc(sizeof(tp_table)*(objeto.qtdCampos+1)); // Aloca esquema com a quantidade de campos necessarios.
    memset(esquema, 0, (objeto.qtdCampos+1)*sizeof(tp_table));
    for (i = 0; i < objeto.qtdCampos+1; i++) {
        esquema[i].next = NULL;
    }


    i = 0;
    if(esquema == NULL){
        free(tupla);
        free(tuplaT);
        return ERRO_DE_ALOCACAO;
    }

    char directory[LEN_DB_NAME*2];
    strcpy(directory, connected.db_directory);
    strcat(directory, "fs_schema.dat");

    schema = fopen(directory, "a+b"); // Abre o arquivo de esquemas de tabelas.

    if (schema == NULL){
        free(tupla);
        free(tuplaT);
        free(esquema);
        return ERRO_ABRIR_ESQUEMA;
    }

    while((fgetc (schema) != EOF) && (i < objeto.qtdCampos)){ // Varre o arquivo ate encontrar todos os campos com o codigo da tabela.
        fseek(schema, -1, 1);

        if(fread(&cod, sizeof(int), 1, schema)){ // Le o codigo da tabela.
            if(cod == objeto.cod){ // Verifica se o campo a ser copiado e da tabela que esta na estrutura fs_objects.

                fread(tupla, sizeof(char), TAMANHO_NOME_CAMPO, schema);
                strcpylower(esquema[i].nome,tupla);                  // Copia dados do campo para o esquema.

                fread(&esquema[i].tipo, sizeof(char),1,schema);
                fread(&esquema[i].tam, sizeof(int),1,schema);
                fread(&esquema[i].chave, sizeof(int),1,schema);

                fread(tuplaT, sizeof(char), TAMANHO_NOME_TABELA, schema);
                strcpylower(esquema[i].tabelaApt,tuplaT);

                fread(tupla, sizeof(char), TAMANHO_NOME_CAMPO, schema);
                strcpylower(esquema[i].attApt,tupla);

                if (i > 0)
                    esquema[i-1].next = &esquema[i];

                i++;
            } else {
                fseek(schema, 109, 1); // Pula a quantidade de caracteres para a proxima verificacao (40B do nome, 1B do tipo e 4B do tamanho,4B da chave, 20B do nome da Tabela Apontada e 40B do atributo apontado).
            }
        }
    }
    esquema[i].next = NULL;

    free(tupla);
    free(tuplaT);
    fclose(schema);

    return esquema;
}