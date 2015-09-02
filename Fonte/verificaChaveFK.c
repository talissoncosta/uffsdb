//BufferPool
#include "buffend.h"

/* ----------------------------------------------------------------------------------------------
    Objetivo:   Gera as verificações em relação a chave FK.
    Parametros: Nome da Tabela, Coluna C, Nome do Campo, Valor do Campo, Tabela Apontada e Atributo Apontado.
    Retorno:    INT
                SUCCESS,
                ERRO_DE_PARAMETRO,
                ERRO_CHAVE_ESTRANGEIRA
   ---------------------------------------------------------------------------------------------*/

int verificaChaveFK(char *nomeTabela,column *c, char *nomeCampo, char *valorCampo, char *tabelaApt, char *attApt){
    int x,j, erro, page;
    char str[20];
    char dat[5] = ".dat";
    struct fs_objects objeto;
    tp_table *tabela;
    tp_buffer *bufferpoll;
    column *pagina = NULL;

    strcpylower(str, tabelaApt);
    strcat(str, dat);              //Concatena e junta o nome com .dat

    erro = existeAtributo(nomeTabela, c);
    /*if(erro != SUCCESS )
        return ERRO_DE_PARAMETRO;*/

    //if(existeAtributo(tabelaApt, c))
        //return ERRO_CHAVE_ESTRANGEIRA;

    if(iniciaAtributos(&objeto, &tabela, &bufferpoll, tabelaApt) != SUCCESS) {
        free(bufferpoll);
        free(tabela);
        return ERRO_DE_PARAMETRO;
    }


    erro = SUCCESS;
    for(x = 0; erro == SUCCESS; x++)
        erro = colocaTuplaBuffer(bufferpoll, x, tabela, objeto);

    for (page = 0; page < PAGES; page++) {
        if (pagina) free(pagina);
        pagina = getPage(bufferpoll, tabela, objeto, page);
        if (!pagina) break;

        for(j = 0; j < objeto.qtdCampos * bufferpoll[page].nrec; j++){
            if (pagina[j].nomeCampo) {
                if(objcmp(pagina[j].nomeCampo, attApt) == 0){

                    if(pagina[j].tipoCampo == 'S'){
                        if(objcmp(pagina[j].valorCampo, valorCampo) == 0){
                            free(pagina);
                            free(bufferpoll);
                            free(tabela);
                            return SUCCESS;
                        }
                    } else if(pagina[j].tipoCampo == 'I'){
                        int *n = (int *)&pagina[j].valorCampo[0];
                        if(*n == atoi(valorCampo)){
                            free(pagina);
                            free(bufferpoll);
                            free(tabela);
                            return SUCCESS;
                        }
                    } else if(pagina[j].tipoCampo == 'D'){
                        double *nn = (double *)&pagina[j].valorCampo[0];

                        if(*nn == atof(valorCampo)){
                            free(pagina);
                            free(bufferpoll);
                            free(tabela);
                            return SUCCESS;
                        }
                    } else if(pagina[j].tipoCampo == 'C'){
                        if(pagina[j].valorCampo == valorCampo){
                            free(pagina);
                            free(bufferpoll);
                            free(tabela);
                            return SUCCESS;
                        }
                    } else {
                        free(pagina);
                        free(bufferpoll);
                        free(tabela);
                        return ERRO_CHAVE_ESTRANGEIRA;
                    }
                }
            }
        }
    }

    if (pagina) free(pagina);
    free(bufferpoll);
    free(tabela);
    return ERRO_CHAVE_ESTRANGEIRA;
}