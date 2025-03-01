#pragma once

#define CAPACIDADE_INICIAL 10

typedef struct {
	void** conteudo;
	int tamanho;
	int capacidade;
} Lista;

/**************************************************************************************************
* Cria uma nova lista e inicializa seus atributos
* @return Refer�ncia para a lista criada
**************************************************************************************************/
Lista* criarLista();

/**************************************************************************************************
* Libera a mem�ria utilizada por uma lista e anula a refer�ncia
* @param lista Refer�ncia para a lista
**************************************************************************************************/
void liberarLista(Lista* lista);

/**************************************************************************************************
* Libera a mem�ria utilizada por elementos de uma lista
* @param elemento Elemento a ser liberado
* @param posicao Posi��o de ocorr�ncia na lista
**************************************************************************************************/
void liberarListaElementos(void* elemento, int posicao);

/**************************************************************************************************
* Adiciona um elemento ao final da lista e redimensiona o vetor interno, se necess�rio
* @param lista Refer�ncia para a lista
* @param elemento Elemento a ser adicionado
**************************************************************************************************/
void adicionarElemento(Lista* lista, void* elemento);

/**************************************************************************************************
* Obt�m um elemento da lista a partir de uma posi��o
* @param lista Refer�ncia para a lista
* @param posicao Posi��o do elemento a ser obtido
**************************************************************************************************/
void* obterElemento(Lista* lista, int posicao);

/**************************************************************************************************
* Remove um elemento da lista a partir de uma posi��o
* @param lista Refer�ncia para a lista
* @param posicao Posi��o do elemento a ser removido
* @return Elemento removido
**************************************************************************************************/
void* removerElemento(Lista* lista, int posicao);

/**************************************************************************************************
* Percorre a lista, aplicando uma fun��o a cada elemento
* @param lista Refer�ncia para a lista
* @param funcao Fun��o a ser aplicada a cada elemento
**************************************************************************************************/
void percorrerLista(Lista* lista, void (*funcao)(void* elemento, int posicao));

/**************************************************************************************************
* Filtra a lista, mantendo apenas os elementos que satisfazem uma condi��o
* @param lista Refer�ncia para a lista
* @param funcao Fun��o de filtragem de elementos
* @return Nova lista com os elementos filtrados
**************************************************************************************************/
Lista* filtrarLista(Lista* lista, int (*funcao)(void* elemento, int posicao));

/**************************************************************************************************
* Busca um elemento na lista a partir de uma condi��o
* @param lista Refer�ncia para a lista
* @param funcao Fun��o de busca de elementos
* @return Posi��o do elemento na lista ou -1, caso n�o seja encontrado
**************************************************************************************************/
int buscarLista(Lista* lista, int (*funcao)(void* elemento, int posicao));
