//BufferPool
#include "buffend.h"

/* ----------------------------------------------------------------------------------------------
    Objetivo:   Função para exclusão de tabelas.
    Parametros: Nome da tabela (char).
    Retorno:    INT
                SUCCESS,
                ERRO_REMOVER_ARQUIVO_OBJECT,
                ERRO_REMOVER_ARQUIVO_SCHEMA,
                ERRO_LEITURA_DADOS.
   ---------------------------------------------------------------------------------------------*/

int excluirTabela(char *nomeTabela) {
    struct fs_objects objeto, objeto1;
    tp_table *esquema, *esquema1;
    int x,erro, i, j, k, l, qtTable;
    char str[20];
    char dat[5] = ".dat";
    memset(str, '\0', 20);

    if (!verificaNomeTabela(nomeTabela)) {
        printf("ERROR: table \"%s\" does not exist.\n", nomeTabela);
        return ERRO_NOME_TABELA;
    }

    strcpylower(str, nomeTabela);
    strcat(str, dat);              //Concatena e junta o nome com .dat

    abreTabela(nomeTabela, &objeto, &esquema);
    qtTable = quantidadeTabelas();

    char **tupla = (char **)malloc(sizeof(char **)*qtTable);
    memset(tupla, 0, qtTable);

    for (i=0; i < qtTable; i++) {
        tupla[i] = (char *)malloc(sizeof(char)*TAMANHO_NOME_TABELA);
        memset(tupla[i], '\0', TAMANHO_NOME_TABELA);
    }

    tp_table *tab2 = (tp_table *)malloc(sizeof(struct tp_table));
    tab2 = procuraAtributoFK(objeto);   //retorna o tipo de chave que e cada campo

    FILE *dicionario;

    char directory[LEN_DB_NAME*2];
    memset(directory, '\0', LEN_DB_NAME*2);

    strcpy(directory, connected.db_directory);
    strcat(directory, "fs_object.dat");

    if((dicionario = fopen(directory,"a+b")) == NULL)
        return ERRO_ABRIR_ARQUIVO;

    k=0;
    while(fgetc (dicionario) != EOF){
        fseek(dicionario, -1, 1);

        //coloca o nome de todas as tabelas em tupla
        fread(tupla[k], sizeof(char), TAMANHO_NOME_TABELA , dicionario);
        k++;

        fseek(dicionario, 28, 1);
    }

    fclose(dicionario);

    for(i = 0; i < objeto.qtdCampos; i++){
        if(tab2[i].chave == PK){
            for(j=0; j<qtTable; j++) {                      //se tiver chave primaria verifica se ela e chave
                if(objcmp(tupla[j], nomeTabela) != 0) {     //estrangeira em outra tabela

                    abreTabela(tupla[j], &objeto1, &esquema1);

                    tp_table *tab3 = (tp_table *)malloc(sizeof(struct tp_table));
                    tab3 = procuraAtributoFK(objeto1);

                    for(l=0; l<objeto1.qtdCampos; l++) {
                        if(tab3[l].chave == FK) { //verifica se a outra tabela possui chave estrangeira. se sim, verifica se e da tabela anterior.
                            if(objcmp(nomeTabela, tab3[l].tabelaApt) == 0) {
                                printf("ERROR: cannot drop table \"%s\" because other objects depend on it.\n", nomeTabela);
                                return ERRO_CHAVE_ESTRANGEIRA;
                            }
                        }
                    }
                    free(tab3);
                }
            }
        }
    }

    free(tab2);

    tp_buffer *bufferpoll = initbuffer();

    if(bufferpoll == ERRO_DE_ALOCACAO){
        printf("ERROR: no memory available to allocate buffer.\n");
        return ERRO_LEITURA_DADOS;
    }

    erro = SUCCESS;
    for(x = 0; erro == SUCCESS; x++)
        erro = colocaTuplaBuffer(bufferpoll, x, esquema, objeto);

    if(procuraSchemaArquivo(objeto) != 0) {
        free(bufferpoll);
        return ERRO_REMOVER_ARQUIVO_SCHEMA;
    }

    if(procuraObjectArquivo(nomeTabela) != 0) {
        free(bufferpoll);
        return ERRO_REMOVER_ARQUIVO_OBJECT;
    }

   	strcpy(directory, connected.db_directory);
    strcat(directory, str);

    remove(directory);

    free(bufferpoll);

    printf("DROP TABLE\n");

    return SUCCESS;
}
