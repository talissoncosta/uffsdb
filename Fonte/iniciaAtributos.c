//BufferPool
#include "buffend.h"

/* ----------------------------------------------------------------------------------------------
    Objetivo:   Inicializa os atributos necessários para a verificação de FK e PK.
    Parametros: Objeto da tabela, Tabela, Buffer e nome da tabela.
    Retorno:    INT
                SUCCESS,
                ERRO_DE_PARAMETRO,
   ---------------------------------------------------------------------------------------------*/

int iniciaAtributos(struct fs_objects *objeto, tp_table **tabela, tp_buffer **bufferpoll, char *nomeT){


    *objeto     = leObjeto(nomeT);
    *tabela     = leSchema(*objeto);
    *bufferpoll = initbuffer();

    if(*tabela == ERRO_ABRIR_ESQUEMA) {
        return ERRO_DE_PARAMETRO;
    }

    if(*bufferpoll == ERRO_DE_ALOCACAO)
        return ERRO_DE_PARAMETRO;

    return SUCCESS;
}