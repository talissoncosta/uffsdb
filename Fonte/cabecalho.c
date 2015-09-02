//BufferPool
#include "buffend.h"

int cabecalho(tp_table *s, int num_reg) {
    int count, aux;
    aux = 0;
    
    for(count = 0; count < num_reg; count++) {
        cria_campo(s[count].tam, 1, s[count].nome, 0); // O segundo parâmetro significa se = 1 Cabecalho se = 0 é valor daquele campo
        aux += s[count].tam;
    }
    printf("\n");
    return aux;
}