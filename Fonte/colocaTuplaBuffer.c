//BufferPool
#include "buffend.h"

int colocaTuplaBuffer(tp_buffer *buffer, int from, tp_table *campos, struct fs_objects objeto){//Define a página que será incluida uma nova tupla

    char *tupla = getTupla(campos,objeto,from);

    if(tupla == ERRO_DE_LEITURA) {
        free(tupla);
        return ERRO_LEITURA_DADOS;
    }

    int i=0, found=0;
    while (!found && i < PAGES) {//Procura pagina com espaço para a tupla.

        if(SIZE - buffer[i].position > tamTupla(campos, objeto)) {// Se na pagina i do buffer tiver espaço para a tupla, coloca tupla.
            setTupla(buffer, tupla, tamTupla(campos, objeto), i);
            found = 1;
            buffer[i].position += tamTupla(campos, objeto); // Atualiza proxima posição vaga dentro da pagina.
            buffer[i].nrec += 1;
            break;
        }
        i++;// Se não, passa pra proxima página do buffer.
    }

    if (!found) {
        free(tupla);
        return ERRO_BUFFER_CHEIO;
    }


    free(tupla);
    return SUCCESS;
}