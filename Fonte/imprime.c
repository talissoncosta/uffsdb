//BufferPool
#include "buffend.h"

/* ----------------------------------------------------------------------------------------------
    Objetivo:   Utilizada para impressão de tabelas (select * from table;).
    Parametros: Nome da tabela (char).
    Retorno:    void.
   ---------------------------------------------------------------------------------------------*/

void imprime(char nomeTabela[]) {

    int j,erro, x, p, cont=0;
    struct fs_objects objeto;

    if(!verificaNomeTabela(nomeTabela)){
        printf("\nERROR: relation \"%s\" was not found.\n\n\n", nomeTabela);
        return;
    }

    objeto = leObjeto(nomeTabela);

    tp_table *esquema = leSchema(objeto);

    if(esquema == ERRO_ABRIR_ESQUEMA){
        printf("ERROR: schema cannot be created.\n");
        free(esquema);
        return;
    }

    tp_buffer *bufferpoll = initbuffer();

    if(bufferpoll == ERRO_DE_ALOCACAO){
        free(bufferpoll);
        free(esquema);
        printf("ERROR: no memory available to allocate buffer.\n");
        return;
    }

    erro = SUCCESS;
    for(x = 0; erro == SUCCESS; x++)
        erro = colocaTuplaBuffer(bufferpoll, x, esquema, objeto);

    int ntuples = --x;
	p = 0;
	while(x){
	    column *pagina = getPage(bufferpoll, esquema, objeto, p);
	    if(pagina == ERRO_PARAMETRO){
            printf("ERROR: could not open the table.\n");
            free(bufferpoll);
            free(esquema);
            return;
	    }

	    if(!cont) {
	        for(j=0; j < objeto.qtdCampos; j++){
	            if(pagina[j].tipoCampo == 'S')
	                printf(" %-20s ", pagina[j].nomeCampo);
	        	else
	                printf(" %-10s ", pagina[j].nomeCampo);
	            if(j<objeto.qtdCampos-1)
	            	printf("|");
	        }
	        printf("\n");
	        for(j=0; j < objeto.qtdCampos; j++){
	            printf("%s",(pagina[j].tipoCampo == 'S')? "----------------------": "------------");
	            if(j<objeto.qtdCampos-1)
	            	printf("+");
	        }
	        printf("\n");
	    }
	    cont++;
		for(j=0; j < objeto.qtdCampos*bufferpoll[p].nrec; j++){
        	if(pagina[j].tipoCampo == 'S')
            	printf(" %-20s ", pagina[j].valorCampo);
        	else if(pagina[j].tipoCampo == 'I'){
            	int *n = (int *)&pagina[j].valorCampo[0];
            	printf(" %-10d ", *n);
        	} else if(pagina[j].tipoCampo == 'C'){
            	printf(" %-10c ", pagina[j].valorCampo[0]);
        	} else if(pagina[j].tipoCampo == 'D'){
            	double *n = (double *)&pagina[j].valorCampo[0];
    	        printf(" %-10f ", *n);
        	}
            if(j>=1 && ((j+1)%objeto.qtdCampos)==0)
            	printf("\n");
        	else
        		printf("|");
    	}
    	x-=bufferpoll[p++].nrec;
    }
    printf("\n(%d %s)\n\n",ntuples,(1>=ntuples)?"row": "rows");

    free(bufferpoll);
    free(esquema);
}
