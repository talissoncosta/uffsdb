//BufferPool
#include "buffend.h"

char retornaTamanhoTipoDoCampo(char *nomeCampo, table  *tab) {

    char tipo = 0;

    tp_table *temp = tab->esquema;

    while(temp != NULL) {

       if (objcmp(nomeCampo,temp->nome) == 0) {
            tipo = temp->tipo;

            return tipo;
       }

       temp = temp->next;
    }

    return tipo;
}
