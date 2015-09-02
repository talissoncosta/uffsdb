//BufferPool
#include "buffend.h"

/* ----------------------------------------------------------------------------------------------
    Objetivo:   Retorna vetor de esquemas com todos os atributos chaves (PK, FK e NPK)
    Parametros: Objeto da tabela.
    Retorno:    Vetor de esquemas vetEsqm
   ---------------------------------------------------------------------------------------------*/

tp_table *procuraAtributoFK(struct fs_objects objeto){
    FILE *schema;
    int cod = 0, chave, i = 0;
    char *tupla = (char *)malloc(sizeof(char) * 109);
    tp_table *esquema = (tp_table *)malloc(sizeof(tp_table)*objeto.qtdCampos);
    tp_table *vetEsqm = (tp_table *)malloc(sizeof(tp_table)*objeto.qtdCampos);
    memset(vetEsqm, 0, sizeof(tp_table)*objeto.qtdCampos);
    memset(esquema, 0, sizeof(tp_table)*objeto.qtdCampos);

    char directory[LEN_DB_NAME*2];
    strcpy(directory, connected.db_directory);
    strcat(directory, "fs_schema.dat");

    if((schema = fopen(directory, "a+b")) == NULL){
        printf("ERROR: could not read schema.\n");
        free(tupla);
		free(esquema);
		free(vetEsqm);
        return ERRO_ABRIR_ESQUEMA;
    }

    while((fgetc (schema) != EOF) && i < objeto.qtdCampos){ // Varre o arquivo ate encontrar todos os campos com o codigo da tabela.
        fseek(schema, -1, 1);

        if(fread(&cod, sizeof(int), 1, schema)){ // Le o codigo da tabela.
            if(cod == objeto.cod){
                fread(tupla, sizeof(char), TAMANHO_NOME_CAMPO, schema);
                strcpylower(esquema[i].nome,tupla);                  // Copia dados do campo para o esquema.

                fread(&esquema[i].tipo , sizeof(char), 1 , schema);
                fread(&esquema[i].tam  , sizeof(int) , 1 , schema);
                fread(&chave, sizeof(int) , 1 , schema);
                vetEsqm[i].tipo = esquema[i].tipo;
                vetEsqm[i].tam = esquema[i].tam;
                fread(tupla, sizeof(char), TAMANHO_NOME_TABELA, schema);
                strcpylower(esquema[i].tabelaApt,tupla);

                fread(tupla, sizeof(char), TAMANHO_NOME_CAMPO, schema);
                strcpylower(esquema[i].attApt,tupla);

                strcpylower(vetEsqm[i].tabelaApt, esquema[i].tabelaApt);
                strcpylower(vetEsqm[i].attApt, esquema[i].attApt);
                strcpylower(vetEsqm[i].nome, esquema[i].nome);
                vetEsqm[i].chave = chave;

                i++;
            } else {
                fseek(schema, 109, 1);
            }
        }
    }
    free(tupla);
	free(esquema);

	fclose(schema);

    return vetEsqm;
}
