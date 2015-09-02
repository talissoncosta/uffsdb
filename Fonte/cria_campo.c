//BufferPool
#include "buffend.h"

// IMPRESSAO BUFFER
void cria_campo(int tam, int header, char *val, int x) {
    int i;
    char aux[30];

    if(header) {
        for(i = 0; i <= 30 && val[i] != '\0'; i++){
            aux[i] = val[i];
        }
        for(;i<30;i++)
            aux[i] = ' ';
        aux[i] ='\0';
        printf("%s", aux);

    } else {
        for(i = 0; i < x; i++)
            printf(" ");
    }
}