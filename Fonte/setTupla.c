//BufferPool
#include "buffend.h"

void setTupla(tp_buffer *buffer,char *tupla, int tam, int pos) { //Coloca uma tupla de tamanho "tam" no buffer e na página "pos"
    int i = buffer[pos].position;

    for (; i < buffer[pos].position + tam; i++)
        buffer[pos].data[i] = *(tupla++);
}