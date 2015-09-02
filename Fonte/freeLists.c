#include "buffend.h"

/* NÃO IMPLEMENTADO: a ideia era dar o free de maneira correta nas listas alocadas ao longo
 * da execução do programa, já que os grupos anteriores não se preocuparam com isso. No entanto,
 * não tivemos tempo ágil para implementar uma solução livre de erros e preferimos deixar
 * dessa maneira.
 */

void freeTp_table(tp_table **tabela, int n) {
	free(tabela);
}


void freeTable(table *tabela) {
	if (tabela != NULL) {
		free(tabela->esquema);
		free(tabela);
	}
}


void freeColumn(column *colunas) {
	if (colunas != NULL) {
		free(colunas);
	}
}