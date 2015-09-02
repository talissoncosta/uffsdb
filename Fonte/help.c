#include <stdlib.h>
#include "buffend.h"

void help() {
	printf("Você está utilizando o DBMS-Interface\n");
	printf("-------------------------- Comandos gerais --------------------------\n");
	printf("Digite:");
	printf("\t\\c NOME\t\t- Para conectar-se no banco NAME\n");
	printf("\t\\q\t\t- Para sair do programa\n");
	printf("----------------- Comandos válidos quando conectado -----------------\n");
	printf("Digite:");
	printf("\t\\d\t\t- Para listar as tabelas do banco\n");
	printf("\t\\l\t\t- Para listar os bancos de dados existentes\n");
	printf("\t\\t NOME\t\t- Para listar os atributos de uma tabela\n\n");
	printf("------------------------------------------------ Sintaxe SQL ------------------------------------------------\n");
	printf("CREATE DATABASE NOME;\t\t\t\t- Cria um novo banco de dados\n");
	printf("\nDROP DATABASE NOME;\t\t\t\t- Exclui um banco de dados\n");
	printf("\nCREATE TABLE NOME (\t\t\t\t- Cria uma nova tabela. Onde 'type' deve\n");
	printf("\tcolumn1 type [attribute][,\t\t  pertencer à {int, integer, double, varchar(SIZE), char}.\n");
	printf("\t...][,\t\t\t\t\t  E 'attribute' pode ser 'PRIMARY KEY', caso seja PK,\n");
	printf("\tcolumnN type [attribute]]\t\t  ou 'REFERENCES NOME(COLUMN)', indicando a tabela\n");
	printf(");\t\t\t\t\t\t  e a coluna que está referenciando (FK).\n");
	printf("\nDROP TABLE NOME;\t\t\t\t- Exclui uma tabela do banco de dados\n");
	printf("\nINSERT INTO NOME [(column1, ..., columnN)]\t- Insere um novo registro na tabela, padrão SQL mas só\n");
	printf("VALUES (1, 'text value', 1.11);\t\t\t  aceita um conjunto de valores. Se as colunas não forem\n");
	printf("\t\t\t\t\t\t  especificadas, a quantidade de valores deve\n");
	printf("\t\t\t\t\t\t  corresponder à quantidade de colunas da tabela.\n");
	printf("\nSELECT * FROM NOME;\t\t\t\t- Não é a implementação padrão do SELECT mas serve para\n");
	printf("\t\t\t\t\t\t  imprmir todos os valores de uma tabela\n");
}