#include <stdio.h>

#include "lista.h"
#include "memoria.h"

Lista* criarLista() {
	Lista* lista = alocarMemoria(sizeof(Lista));

	lista->conteudo = alocarMemoria(CAPACIDADE_INICIAL * sizeof(void*));
	lista->tamanho = 0;
	lista->capacidade = CAPACIDADE_INICIAL;

	return lista;
}

void liberarLista(Lista* lista) {
	if (lista != NULL) {
		liberarMemoria(&lista->conteudo);
		liberarMemoria(&lista);
	}
}

void liberarListaElementos(void* elemento, int posicao) {
	if (elemento != NULL) {
		liberarMemoria(&elemento);
	}
}

void adicionarElemento(Lista* lista, void* elemento) {
	if (lista == NULL || elemento == NULL) {
		fprintf(stderr, "Erro ao adicionar elemento na lista: parametros nulos\n");
		exit(2);
	}

	if (lista->tamanho == lista->capacidade) {
		lista->conteudo = realocarMemoria(lista->conteudo, 2 * lista->capacidade * sizeof(void*));
		lista->capacidade *= 2;
	}

	lista->conteudo[lista->tamanho++] = elemento;
}

void* obterElemento(Lista* lista, int posicao) {
	if (lista == NULL) {
		fprintf(stderr, "Erro ao obter elemento da lista: parametros nulos\n");
		exit(2);
	}

	if (posicao < 0 || posicao >= lista->tamanho) {
		fprintf(stderr, "Erro ao obter elemento da lista: parametros invalidos\n");
		exit(3);
	}

	return lista->conteudo[posicao];
}

void* removerElemento(Lista* lista, int posicao) {
	if (lista == NULL) {
		fprintf(stderr, "Erro ao remover elemento da lista: parametros nulos\n");
		exit(2);
	}

	if (posicao < 0 || posicao >= lista->tamanho) {
		fprintf(stderr, "Erro ao remover elemento da lista: parametros invalidos\n");
		exit(3);
	}

	void* elemento = lista->conteudo[posicao];

	for (int i = posicao, tamanho = lista->tamanho--; i < tamanho; i++) {
		lista->conteudo[i] = lista->conteudo[i + 1];
	}

	return elemento;
}

void percorrerLista(Lista* lista, void (*funcao)(void* elemento, int posicao)) {
	if (lista == NULL || funcao == NULL) {
		fprintf(stderr, "Erro ao percorrer lista: parametros nulos\n");
		exit(2);
	}

	for (int i = 0; i < lista->tamanho; i++) {
		funcao(lista->conteudo[i], i);
	}
}

Lista* filtrarLista(Lista* lista, int (*funcao)(void* elemento, int posicao)) {
	if (lista == NULL || funcao == NULL) {
		fprintf(stderr, "Erro ao filtrar lista: parametros nulos\n");
		exit(2);
	}

	Lista* resultado = criarLista();

	for (int i = 0; i < lista->tamanho; i++) {
		if (funcao(lista->conteudo[i], i)) {
			adicionarElemento(resultado, lista->conteudo[i]);
		}
	}

	return resultado;
}

int buscarLista(Lista* lista, int (*funcao)(void* elemento, int posicao)) {
	if (lista == NULL || funcao == NULL) {
		fprintf(stderr, "Erro ao buscar elemento na lista: parametros nulos\n");
		exit(2);
	}

	for (int i = 0; i < lista->tamanho; i++) {
		if (funcao(lista->conteudo[i], i)) {
			return i;
		}
	}

	return -1;
}
