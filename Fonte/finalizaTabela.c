//BufferPool
#include "buffend.h"

int finalizaTabela(table *t){
    if(t == NULL)
        return ERRO_DE_PARAMETRO;

    FILE *esquema, *dicionario;
    tp_table *aux;
    int codTbl = quantidadeTabelas() + 1, qtdCampos = 0; // Conta a quantidade de tabelas já no dicionario e soma 1 no codigo dessa nova tabela.
    char nomeArquivo[TAMANHO_NOME_ARQUIVO];
    memset(nomeArquivo, 0, TAMANHO_NOME_ARQUIVO);

    char directory[LEN_DB_NAME*2];
    strcpy(directory, connected.db_directory);
    strcat(directory, "fs_schema.dat");

    if((esquema = fopen(directory,"a+b")) == NULL)
        return ERRO_ABRIR_ARQUIVO;

    for(aux = t->esquema; aux != NULL; aux = aux->next){ // Salva novos campos no esquema da tabela, fs_schema.dat

        fwrite(&codTbl         ,sizeof(codTbl)         ,1,esquema);  //Código Tabela
        fwrite(&aux->nome      ,sizeof(aux->nome)      ,1,esquema);  //Nome campo
        fwrite(&aux->tipo      ,sizeof(aux->tipo)      ,1,esquema);  //Tipo campo
        fwrite(&aux->tam       ,sizeof(aux->tam)       ,1,esquema);  //Tamanho campo
        fwrite(&aux->chave     ,sizeof(aux->chave)     ,1,esquema);  //Chave do campo
        fwrite(&aux->tabelaApt ,sizeof(aux->tabelaApt) ,1,esquema);  //Tabela Apontada
        fwrite(&aux->attApt    ,sizeof(aux->attApt)    ,1,esquema);  //Atributo apontado.

        qtdCampos++; // Soma quantidade total de campos inseridos.
    }

    fclose(esquema);

    strcpy(directory, connected.db_directory);
    strcat(directory, "fs_object.dat");

    if((dicionario = fopen(directory,"a+b")) == NULL)
        return ERRO_ABRIR_ARQUIVO;

    strcpylower(nomeArquivo, t->nome);
    strcat(nomeArquivo, ".dat\0");
    strcat(t->nome, "\0");
    // Salva dados sobre a tabela no dicionario.
    fwrite(&t->nome,sizeof(t->nome),1,dicionario);
    fwrite(&codTbl,sizeof(codTbl),1,dicionario);
    fwrite(&nomeArquivo,sizeof(nomeArquivo),1,dicionario);
    fwrite(&qtdCampos,sizeof(qtdCampos),1,dicionario);

    fclose(dicionario);
    return SUCCESS;
}