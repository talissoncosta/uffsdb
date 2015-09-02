//BufferPool
#include "buffend.h"

// CRIA TABELA
table *iniciaTabela(char *nome){
    if(verificaNomeTabela(nome)){   // Se o nome já existir no dicionario, retorna erro.
        return ERRO_NOME_TABELA_INVALIDO;
    }

    table *t = (table *)malloc(sizeof(table)*1);
    memset(t,0,sizeof(table));
    strcpylower(t->nome,nome); // Inicia a estrutura de tabela com o nome da tabela.
    t->esquema = NULL; // Inicia o esquema da tabela com NULL.
    return t; // Retorna estrutura para criação de uma tabela.
}