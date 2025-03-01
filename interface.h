#pragma once

#include "lista.h"

typedef struct {
	const char* descricao;
	void (*comando)();
} MenuItem;

typedef struct {
	const char* titulo;
	Lista* itens;
} Menu;

typedef struct {
	const char* campo;
	const char* valorPadrao;
	const char* valorInformado;
} FormularioItem;

typedef struct {
	const char* titulo;
	Lista* itens;
} Formulario;

typedef struct {
	Lista* colunas;
} TabelaItem;

typedef struct {
	const char* titulo;
	int largura;
} TabelaCabecalho;

typedef struct {
	Lista* cabecalho;
	Lista* itens;
} Tabela;

/**************************************************************************************************
* Cria um novo menu e inicializa seus atributos
* @param titulo T�tulo do menu
* @return Refer�ncia para o menu criado
**************************************************************************************************/
Menu* criarMenu(const char* titulo);

/**************************************************************************************************
* Libera a mem�ria utilizada por um menu e anula a refer�ncia
* @param menu Refer�ncia para o menu
**************************************************************************************************/
void liberarMenu(Menu* menu);

/**************************************************************************************************
* Libera a mem�ria utilizada por elementos de uma lista de menus
* @param elemento Elemento a ser liberado
* @param posicao Posi��o de ocorr�ncia na lista
**************************************************************************************************/
void liberarListaMenu(void* elemento, int posicao);

/**************************************************************************************************
* Cria um novo item de menu e inicializa seus atributos
* @param descricao Descri��o do item de menu
* @param comando Fun��o de comando do item de menu
* @return Refer�ncia para o item de menu criado
**************************************************************************************************/
MenuItem* criarMenuItem(const char* descricao, void (*comando)());

/**************************************************************************************************
* Cria um novo item de menu e inicializa seus atributos
* @param descricao Descri��o do item de menu
* @param comando Fun��o de comando do item de menu
* @return Refer�ncia para o item de menu criado
**************************************************************************************************/
void liberarMenuItem(MenuItem* menuItem);

/**************************************************************************************************
* Libera a mem�ria utilizada por elementos de uma lista de itens de menu
* @param elemento Elemento a ser liberado
* @param posicao Posi��o de ocorr�ncia na lista
**************************************************************************************************/
void liberarListaMenuItem(void* elemento, int posicao);

/**************************************************************************************************
* Adiciona um item de menu a um menu
* @param menu Menu de destino
* @param item Item de menu a ser adicionado
**************************************************************************************************/
void adicionarMenuItem(Menu* menu, MenuItem* item);

/**************************************************************************************************
* Remove um item de menu de um menu
* @param menu Menu de destino
* @param posicao Posi��o do item de menu a ser removido
**************************************************************************************************/
void removerMenuItem(Menu* menu, int posicao);

/**************************************************************************************************
* Cria um novo item de formul�rio e inicializa seus atributos
* @param campo Campo do formul�rio
* @param valorPadrao Valor padr�o do formul�rio
* @return Refer�ncia para o item de formul�rio criado
**************************************************************************************************/
FormularioItem* criarFormularioItem(const char* campo, const char* valorPadrao);

/**************************************************************************************************
* Libera a mem�ria utilizada por um item de formul�rio e anula a refer�ncia
* @param formularioItem Refer�ncia para o item de formul�rio
**************************************************************************************************/
void liberarFormularioItem(FormularioItem* formularioItem);

/**************************************************************************************************
* Libera a mem�ria utilizada por elementos de uma lista de itens de formul�rio
* @param elemento Elemento a ser liberado
* @param posicao Posi��o de ocorr�ncia na lista
**************************************************************************************************/
void liberarListaFormularioItem(void* elemento, int posicao);

/**************************************************************************************************
* Cria um novo formul�rio e inicializa seus atributos
* @param titulo T�tulo do formul�rio
* @return Refer�ncia para o formul�rio criado
**************************************************************************************************/
Formulario* criarFormulario(const char* titulo);

/**************************************************************************************************
* Libera a mem�ria utilizada por um formul�rio e anula a refer�ncia
* @param formulario Refer�ncia para o formul�rio
**************************************************************************************************/
void liberarFormulario(Formulario* formulario);

/**************************************************************************************************
* Libera a mem�ria utilizada por elementos de uma lista de formul�rios
* @param elemento Elemento a ser liberado
* @param posicao Posi��o de ocorr�ncia na lista
**************************************************************************************************/
void liberarListaFormulario(void* elemento, int posicao);

/**************************************************************************************************
* Adiciona um item de formul�rio a um formul�rio
* @param formulario Formul�rio de destino
* @param item Item de formul�rio a ser adicionado
**************************************************************************************************/
void adicionarFormularioItem(Formulario* formulario, FormularioItem* item);

/**************************************************************************************************
* Remove um item de formul�rio de um formul�rio
* @param formulario Formul�rio de destino
* @param posicao Posi��o do item de formul�rio a ser removido
**************************************************************************************************/
void removerFormularioItem(Formulario* formulario, int posicao);

/**************************************************************************************************
* Cria um novo item de tabela e inicializa seus atributos
* @return Refer�ncia para o item de tabela criado
**************************************************************************************************/
TabelaItem* criarTabelaItem();

/**************************************************************************************************
* Libera a mem�ria utilizada por um item de tabela e anula a refer�ncia
* @param tabelaItem Refer�ncia para o item de tabela
**************************************************************************************************/
void liberarTabelaItem(TabelaItem* tabelaItem);

/**************************************************************************************************
* Libera a mem�ria utilizada por elementos de uma lista de itens de tabela
* @param elemento Elemento a ser liberado
* @param posicao Posi��o de ocorr�ncia na lista
**************************************************************************************************/
void liberarListaTabelaItem(void* elemento, int posicao);

/**************************************************************************************************
* Adiciona uma coluna a um item de tabela
* @param tabelaItem Item de tabela de destino
* @param valor Valor da coluna a ser adicionada
**************************************************************************************************/
void adicionarColunaTabelaItem(TabelaItem* tabelaItem, const char* valor);

/**************************************************************************************************
* Remove uma coluna de um item de tabela
* @param tabelaItem Item de tabela de destino
* @param posicao Posi��o da coluna a ser removida
**************************************************************************************************/
void removerColunaTabelaItem(TabelaItem* tabelaItem, int posicao);

/**************************************************************************************************
* Cria um novo cabe�alho de tabela e inicializa seus atributos
* @param titulo T�tulo do cabe�alho
* @return Refer�ncia para o cabe�alho de tabela criado
**************************************************************************************************/
TabelaCabecalho* criarTabelaCabecalho(const char* titulo);

/**************************************************************************************************
* Libera a mem�ria utilizada por um cabe�alho de tabela e anula a refer�ncia
* @param tabelaCabecalho Refer�ncia para o cabe�alho de tabela
**************************************************************************************************/
void liberarTabelaCabecalho(TabelaCabecalho* tabelaCabecalho);

/**************************************************************************************************
* Libera a mem�ria utilizada por elementos de uma lista de cabe�alhos de tabela
* @param elemento Elemento a ser liberado
* @param posicao Posi��o de ocorr�ncia na lista
**************************************************************************************************/
void liberarListaTabelaCabecalho(void* elemento, int posicao);

/**************************************************************************************************
* Cria uma nova tabela e inicializa seus atributos
* @return Refer�ncia para a tabela criada
**************************************************************************************************/
Tabela* criarTabela();

/**************************************************************************************************
* Libera a mem�ria utilizada por uma tabela e anula a refer�ncia
* @param tabela Refer�ncia para a tabela
**************************************************************************************************/
void liberarTabela(Tabela* tabela);

/**************************************************************************************************
* Libera a mem�ria utilizada por elementos de uma lista de tabelas
* @param elemento Elemento a ser liberado
* @param posicao Posi��o de ocorr�ncia na lista
**************************************************************************************************/
void liberarListaTabela(void* elemento, int posicao);

/**************************************************************************************************
* Adiciona um cabe�alho a uma tabela
* @param tabela Tabela de destino
* @param tabelaCabecalho Cabe�alho a ser adicionado
**************************************************************************************************/
void adicionarTabelaCabecalho(Tabela* tabela, TabelaCabecalho* tabelaCabecalho);

/**************************************************************************************************
* Remove um cabe�alho de uma tabela
* @param tabela Tabela de destino
* @param posicao Posi��o do cabe�alho a ser removido
**************************************************************************************************/
void removerTabelaCabecalho(Tabela* tabela, int posicao);

/**************************************************************************************************
* Adiciona um item a uma tabela
* @param tabela Tabela de destino
* @param tabelaItem Item a ser adicionado
**************************************************************************************************/
void adicionarTabelaItem(Tabela* tabela, TabelaItem* tabelaItem);

/**************************************************************************************************
* Remove um item de uma tabela
* @param tabela Tabela de destino
* @param posicao Posi��o do item a ser removido
* @return Refer�ncia para o item removido
**************************************************************************************************/
void removerTabelaItem(Tabela* tabela, int posicao);

/**************************************************************************************************
* Exibe um menu na sa�da do console
* @param menu Menu a ser exibido
**************************************************************************************************/
void exibirMenu(Menu* menu);

/**************************************************************************************************
* Exibe um formul�rio na sa�da do console
* @param formulario Formul�rio a ser exibido
**************************************************************************************************/
void exibirFormulario(Formulario* formulario);

/**************************************************************************************************
* Exibe uma tabela na sa�da do console
* @param tabela Tabela a ser exibida
**************************************************************************************************/
void exibirTabela(Tabela* tabela);

/**************************************************************************************************
* L� uma entrada do console
* @param entrada String para armazenar a entrada
* @param tamanho Tamanho da string de entrada
**************************************************************************************************/
void lerEntrada(char* entrada, int tamanho);

/**************************************************************************************************
* L� um n�mero inteiro do console
* @param entrada String para armazenar a entrada
* @param tamanho Tamanho da string de entrada
* @return N�mero inteiro lido ou -1, se a entrada n�o for v�lida
**************************************************************************************************/
int lerInteiro(char* entrada, int tamanho);

/**************************************************************************************************
* Converte uma string em um n�mero inteiro
* @param entrada String a ser convertida
* @return N�mero inteiro convertido ou -1, se a convers�o n�o for poss�vel
**************************************************************************************************/
int converterInteiro(const char* entrada);

/**************************************************************************************************
* L� um n�mero decimal do console
* @param entrada String para armazenar a entrada
* @param tamanho Tamanho da string de entrada
* @return N�mero decimal lido ou -1, se a entrada n�o for v�lida
**************************************************************************************************/
float lerDecimal(char* entrada, int tamanho);

/**************************************************************************************************
* Converte uma string em um n�mero decimal
* @param entrada String a ser convertida
* @return N�mero decimal convertido ou -1, se a convers�o n�o for poss�vel
**************************************************************************************************/
float converterDecimal(const char* entrada);

/**************************************************************************************************
* Remove os caracteres excendentes da entrada padr�o
**************************************************************************************************/
void limparEntrada();

/**************************************************************************************************
* Limpa a tela do console
**************************************************************************************************/
void limparConsole();
