//BufferPool
#include "buffend.h"

/* ---------------------------------------------------------------------------------------------- 
    Objetivo:   Recebe o nome de uma tabela e engloba as funções leObjeto() e leSchema().
    Parametros: Nome da Tabela, Objeto da Tabela e tabela.
    Retorno:    tp_table
   ---------------------------------------------------------------------------------------------*/

tp_table *abreTabela(char *nomeTabela, struct fs_objects *objeto, tp_table **tabela) {
    *objeto     = leObjeto(nomeTabela);
    *tabela     = leSchema(*objeto);

    return *tabela;
}
