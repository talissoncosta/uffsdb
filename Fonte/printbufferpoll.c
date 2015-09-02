//BufferPool
#include "buffend.h"

int printbufferpoll(tp_buffer *buffpoll, tp_table *s,struct fs_objects objeto, int num_page){
    
    int aux, i, num_reg = objeto.qtdCampos;
    
    
    if(buffpoll[num_page].nrec == 0){
        return ERRO_IMPRESSAO;  
    }
    
    i = aux = 0;
    
    aux = cabecalho(s, num_reg);
    

    while(i < buffpoll[num_page].nrec){ // Enquanto i < numero de registros * tamanho de uma instancia da tabela
        drawline(buffpoll, s, objeto, i, num_page);
        i++;
    }
    return SUCCESS;
}