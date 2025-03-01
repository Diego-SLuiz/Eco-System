#pragma once

#define CAPACIDADE_INICIAL 10

typedef struct {
	void** conteudo;
	int tamanho;
	int capacidade;
} Lista;

/**************************************************************************************************
* Cria uma nova lista e inicializa seus atributos
* @return Referência para a lista criada
**************************************************************************************************/
Lista* criarLista();

/**************************************************************************************************
* Libera a memória utilizada por uma lista e anula a referência
* @param lista Referência para a lista
**************************************************************************************************/
void liberarLista(Lista* lista);

/**************************************************************************************************
* Libera a memória utilizada por elementos de uma lista
* @param elemento Elemento a ser liberado
* @param posicao Posição de ocorrência na lista
**************************************************************************************************/
void liberarListaElementos(void* elemento, int posicao);

/**************************************************************************************************
* Adiciona um elemento ao final da lista e redimensiona o vetor interno, se necessário
* @param lista Referência para a lista
* @param elemento Elemento a ser adicionado
**************************************************************************************************/
void adicionarElemento(Lista* lista, void* elemento);

/**************************************************************************************************
* Obtém um elemento da lista a partir de uma posição
* @param lista Referência para a lista
* @param posicao Posição do elemento a ser obtido
**************************************************************************************************/
void* obterElemento(Lista* lista, int posicao);

/**************************************************************************************************
* Remove um elemento da lista a partir de uma posição
* @param lista Referência para a lista
* @param posicao Posição do elemento a ser removido
* @return Elemento removido
**************************************************************************************************/
void* removerElemento(Lista* lista, int posicao);

/**************************************************************************************************
* Percorre a lista, aplicando uma função a cada elemento
* @param lista Referência para a lista
* @param funcao Função a ser aplicada a cada elemento
**************************************************************************************************/
void percorrerLista(Lista* lista, void (*funcao)(void* elemento, int posicao));

/**************************************************************************************************
* Filtra a lista, mantendo apenas os elementos que satisfazem uma condição
* @param lista Referência para a lista
* @param funcao Função de filtragem de elementos
* @return Nova lista com os elementos filtrados
**************************************************************************************************/
Lista* filtrarLista(Lista* lista, int (*funcao)(void* elemento, int posicao));

/**************************************************************************************************
* Busca um elemento na lista a partir de uma condição
* @param lista Referência para a lista
* @param funcao Função de busca de elementos
* @return Posição do elemento na lista ou -1, caso não seja encontrado
**************************************************************************************************/
int buscarLista(Lista* lista, int (*funcao)(void* elemento, int posicao));
