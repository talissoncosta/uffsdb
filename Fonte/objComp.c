#include "buffend.h"
#include <string.h>
#include <ctype.h>

int objcmp(char *obj, char *str) {
	char *object, *string;
	int i;

	object = (char *)malloc(sizeof(char)*TAMANHO_NOME_CAMPO);
	string = (char *)malloc(sizeof(char)*TAMANHO_NOME_CAMPO);
	memset(object, '\0', TAMANHO_NOME_CAMPO);
	memset(string, '\0', TAMANHO_NOME_CAMPO);

	for (i = 0; i < strlen(obj); i++)
		object[i] = tolower(obj[i]);
	object[i] = '\0';

	for (i = 0; i < strlen(str); i++)
		string[i] = tolower(str[i]);
	string[i] = '\0';

	i = strcmp(object, string);

	free(object);
	free(string);

	return i;
}

void strcpylower(char *dest, char *src) {
	int n = strlen(src),
		i = 0;

	do {
		*dest++ = tolower(*src++);
		if (i++ == n) break;
	} while (*src != '\0');

	*dest = '\0';
}

void strncpylower(char *dest, char *src, int length) {
	int i = 0;
	while (i < length) {
		if (src[i] == '\0') break;
		dest[i] = tolower(src[i]);
		i++;
	}

	dest[i] = '\0';
}