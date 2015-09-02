//BufferPool
#include "buffend.h"

int retornaTamanhoValorCampo(char *nomeCampo, table  *tab) {

    int tam = 0;

    tp_table *temp = tab->esquema;

    while(temp != NULL) {

       if (objcmp(nomeCampo,temp->nome) == 0) {
            tam = temp->tam;

            return tam;
       }

       temp = temp->next;
    }

    return tam;
}