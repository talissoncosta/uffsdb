//BufferPool
#include "buffend.h"

// EXCLUIR TUPLA BUFFER
column * excluirTuplaBuffer(tp_buffer *buffer, tp_table *campos, struct fs_objects objeto, int page, int nTupla){
    column *colunas = (column *)malloc(sizeof(column)*objeto.qtdCampos);

    if(colunas == NULL)
        return ERRO_DE_ALOCACAO;

    if(buffer[page].nrec == 0) //Essa página não possui registros
        return ERRO_PARAMETRO;

    int i, tamTpl = tamTupla(campos, objeto), j=0, t=0;
    i = tamTpl*nTupla; //Calcula onde começa o registro

    while(i < tamTpl*nTupla+tamTpl){
        t=0;

        colunas[j].valorCampo = (char *)malloc(sizeof(char)*campos[j].tam); //Aloca a quantidade necessária para cada campo
        colunas[j].tipoCampo = campos[j].tipo;  // Guarda o tipo do campo
        strcpylower(colunas[j].nomeCampo, campos[j].nome);   //Guarda o nome do campo

        while(t < campos[j].tam){
            colunas[j].valorCampo[t] = buffer[page].data[i];    //Copia os dados
            t++;
            i++;
        }
        j++;
    }
    j = i;
    i = tamTpl*nTupla;
    for(; i < buffer[page].position; i++, j++) //Desloca os bytes do buffer sobre a tupla excluida
        buffer[page].data[i] = buffer[page].data[j];

    buffer[page].position -= tamTpl;
    buffer[page].nrec--;

    return colunas; //Retorna a tupla excluida do buffer
}