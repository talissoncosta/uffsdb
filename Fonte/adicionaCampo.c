//BufferPool
#include "buffend.h"

table *adicionaCampo(table *t,char *nomeCampo, char tipoCampo, int tamanhoCampo, int tChave, char *tabelaApt, char *attApt){
    tp_table *e = NULL;

    if(t == NULL) // Se a estrutura passada for nula, retorna erro.
        return ERRO_ESTRUTURA_TABELA_NULA;
    tp_table *aux;
    if(t->esquema == NULL){ // Se o campo for o primeiro a ser adicionado, adiciona campo no esquema.


        e = (tp_table *)malloc(sizeof(tp_table));
        memset(e, 0, sizeof(tp_table));
        if (e == NULL) {
            return ERRO_DE_ALOCACAO;
        }
        e->next = NULL;
        int n = strlen(nomeCampo)+1;

        if (n > TAMANHO_NOME_CAMPO) {
            n = TAMANHO_NOME_CAMPO;
        }

        strncpylower(e->nome, nomeCampo,n); // Copia nome do campo passado para o esquema
        e->tipo = tipoCampo; // Copia tipo do campo passado para o esquema
        e->tam = tamanhoCampo; // Copia tamanho do campo passado para o esquema
        e->chave = tChave; // Copia tipo de chave passado para o esquema

        if(strlen(tabelaApt) >= 1)
            strcpylower(e->tabelaApt, tabelaApt); //Copia a Tabela Refenciada da FK de chave passado para o esquema;

        if(strlen(attApt) >= 1)
            strcpylower(e->attApt, attApt); //Copia o Atributo Refenciado da FK de chave passado para o esquema

        t->esquema = e;

        return t; // Retorna a estrutura
    } else {
        for(aux = t->esquema; aux != NULL; aux = aux->next){ // Anda até o final da estrutura de campos.
            if(aux->next == NULL){ // Adiciona um campo no final.
                e = (tp_table *)malloc(sizeof(tp_table));
                memset(e, 0, sizeof(*e));

                if (e == NULL) {
                    return ERRO_DE_ALOCACAO;
                }

                e->next = NULL;

                int n = strlen(nomeCampo)+1;

                if (n > TAMANHO_NOME_CAMPO) {
                    n = TAMANHO_NOME_CAMPO;
                }

                strncpylower(e->nome, nomeCampo,n); // Copia nome do campo passado para o esquema
                e->tipo = tipoCampo; // Copia tipo do campo passado para o esquema
                e->tam = tamanhoCampo; // Copia tamanho do campo passado para o esquema
                e->chave = tChave; // Copia tipo de chave passado para o esquema

                strcpylower(e->tabelaApt, tabelaApt); //Copia a Tabela Refenciada da FK de chave passado para o esquema;

                strcpylower(e->attApt, attApt); //Copia o Atributo Refenciado da FK de chave passado para o esquema

                aux->next = e; // Faz o campo anterior apontar para o campo inserido.
                return t;
            }
        }
    }

    return t; //Retorna estrutura atualizada.
}