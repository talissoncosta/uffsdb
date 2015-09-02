//BufferPool
#include "buffend.h"

// INICIALIZACAO DO BUFFER
tp_buffer * initbuffer(){

    tp_buffer *bp = (tp_buffer*)malloc(sizeof(tp_buffer)*PAGES);
    memset(bp, 0, sizeof(tp_buffer)*PAGES);

    int i;
    tp_buffer *temp = bp;

    if(bp == NULL)
        return ERRO_DE_ALOCACAO;
    for (i = 0;i < PAGES; i++){
        temp->db=0;
        temp->pc=0;
        temp->nrec=0;
        temp++;
    }

    return bp;
}