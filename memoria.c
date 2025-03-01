#include <stdio.h>
#include <string.h>

#include "memoria.h"

void* alocarMemoria(size_t quantidade) {
	void* memoria = calloc(1, quantidade);

	if (memoria == NULL) {
		perror("Erro ao alocar memoria");
		exit(1);
	}

	return memoria;
}

void* realocarMemoria(void* referencia, size_t quantidade) {
	if (referencia == NULL) {
		fprintf(stderr, "Erro ao realocar memoria: parametros nulos\n");
		exit(2);
	}

	void* memoria = realloc(referencia, quantidade);

	if (memoria == NULL) {
		perror("Erro ao realocar memoria");
		exit(1);
	}

	return memoria;
}

void liberarMemoria(void** referencia) {
	if (referencia != NULL && *referencia != NULL) {
		free(*referencia);
		*referencia = NULL;
	}
}

char* duplicarString(const char* string) {
	if (string == NULL) {
		fprintf(stderr, "Erro ao duplicar string: parametros nulos\n");
		exit(2);
	}

	char* copia = strdup(string);

	if (copia == NULL) {
		perror("Erro ao duplicar string");
		exit(1);
	}

	return copia;
}
