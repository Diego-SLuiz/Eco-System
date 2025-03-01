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
* @param titulo Título do menu
* @return Referência para o menu criado
**************************************************************************************************/
Menu* criarMenu(const char* titulo);

/**************************************************************************************************
* Libera a memória utilizada por um menu e anula a referência
* @param menu Referência para o menu
**************************************************************************************************/
void liberarMenu(Menu* menu);

/**************************************************************************************************
* Libera a memória utilizada por elementos de uma lista de menus
* @param elemento Elemento a ser liberado
* @param posicao Posição de ocorrência na lista
**************************************************************************************************/
void liberarListaMenu(void* elemento, int posicao);

/**************************************************************************************************
* Cria um novo item de menu e inicializa seus atributos
* @param descricao Descrição do item de menu
* @param comando Função de comando do item de menu
* @return Referência para o item de menu criado
**************************************************************************************************/
MenuItem* criarMenuItem(const char* descricao, void (*comando)());

/**************************************************************************************************
* Cria um novo item de menu e inicializa seus atributos
* @param descricao Descrição do item de menu
* @param comando Função de comando do item de menu
* @return Referência para o item de menu criado
**************************************************************************************************/
void liberarMenuItem(MenuItem* menuItem);

/**************************************************************************************************
* Libera a memória utilizada por elementos de uma lista de itens de menu
* @param elemento Elemento a ser liberado
* @param posicao Posição de ocorrência na lista
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
* @param posicao Posição do item de menu a ser removido
**************************************************************************************************/
void removerMenuItem(Menu* menu, int posicao);

/**************************************************************************************************
* Cria um novo item de formulário e inicializa seus atributos
* @param campo Campo do formulário
* @param valorPadrao Valor padrão do formulário
* @return Referência para o item de formulário criado
**************************************************************************************************/
FormularioItem* criarFormularioItem(const char* campo, const char* valorPadrao);

/**************************************************************************************************
* Libera a memória utilizada por um item de formulário e anula a referência
* @param formularioItem Referência para o item de formulário
**************************************************************************************************/
void liberarFormularioItem(FormularioItem* formularioItem);

/**************************************************************************************************
* Libera a memória utilizada por elementos de uma lista de itens de formulário
* @param elemento Elemento a ser liberado
* @param posicao Posição de ocorrência na lista
**************************************************************************************************/
void liberarListaFormularioItem(void* elemento, int posicao);

/**************************************************************************************************
* Cria um novo formulário e inicializa seus atributos
* @param titulo Título do formulário
* @return Referência para o formulário criado
**************************************************************************************************/
Formulario* criarFormulario(const char* titulo);

/**************************************************************************************************
* Libera a memória utilizada por um formulário e anula a referência
* @param formulario Referência para o formulário
**************************************************************************************************/
void liberarFormulario(Formulario* formulario);

/**************************************************************************************************
* Libera a memória utilizada por elementos de uma lista de formulários
* @param elemento Elemento a ser liberado
* @param posicao Posição de ocorrência na lista
**************************************************************************************************/
void liberarListaFormulario(void* elemento, int posicao);

/**************************************************************************************************
* Adiciona um item de formulário a um formulário
* @param formulario Formulário de destino
* @param item Item de formulário a ser adicionado
**************************************************************************************************/
void adicionarFormularioItem(Formulario* formulario, FormularioItem* item);

/**************************************************************************************************
* Remove um item de formulário de um formulário
* @param formulario Formulário de destino
* @param posicao Posição do item de formulário a ser removido
**************************************************************************************************/
void removerFormularioItem(Formulario* formulario, int posicao);

/**************************************************************************************************
* Cria um novo item de tabela e inicializa seus atributos
* @return Referência para o item de tabela criado
**************************************************************************************************/
TabelaItem* criarTabelaItem();

/**************************************************************************************************
* Libera a memória utilizada por um item de tabela e anula a referência
* @param tabelaItem Referência para o item de tabela
**************************************************************************************************/
void liberarTabelaItem(TabelaItem* tabelaItem);

/**************************************************************************************************
* Libera a memória utilizada por elementos de uma lista de itens de tabela
* @param elemento Elemento a ser liberado
* @param posicao Posição de ocorrência na lista
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
* @param posicao Posição da coluna a ser removida
**************************************************************************************************/
void removerColunaTabelaItem(TabelaItem* tabelaItem, int posicao);

/**************************************************************************************************
* Cria um novo cabeçalho de tabela e inicializa seus atributos
* @param titulo Título do cabeçalho
* @return Referência para o cabeçalho de tabela criado
**************************************************************************************************/
TabelaCabecalho* criarTabelaCabecalho(const char* titulo);

/**************************************************************************************************
* Libera a memória utilizada por um cabeçalho de tabela e anula a referência
* @param tabelaCabecalho Referência para o cabeçalho de tabela
**************************************************************************************************/
void liberarTabelaCabecalho(TabelaCabecalho* tabelaCabecalho);

/**************************************************************************************************
* Libera a memória utilizada por elementos de uma lista de cabeçalhos de tabela
* @param elemento Elemento a ser liberado
* @param posicao Posição de ocorrência na lista
**************************************************************************************************/
void liberarListaTabelaCabecalho(void* elemento, int posicao);

/**************************************************************************************************
* Cria uma nova tabela e inicializa seus atributos
* @return Referência para a tabela criada
**************************************************************************************************/
Tabela* criarTabela();

/**************************************************************************************************
* Libera a memória utilizada por uma tabela e anula a referência
* @param tabela Referência para a tabela
**************************************************************************************************/
void liberarTabela(Tabela* tabela);

/**************************************************************************************************
* Libera a memória utilizada por elementos de uma lista de tabelas
* @param elemento Elemento a ser liberado
* @param posicao Posição de ocorrência na lista
**************************************************************************************************/
void liberarListaTabela(void* elemento, int posicao);

/**************************************************************************************************
* Adiciona um cabeçalho a uma tabela
* @param tabela Tabela de destino
* @param tabelaCabecalho Cabeçalho a ser adicionado
**************************************************************************************************/
void adicionarTabelaCabecalho(Tabela* tabela, TabelaCabecalho* tabelaCabecalho);

/**************************************************************************************************
* Remove um cabeçalho de uma tabela
* @param tabela Tabela de destino
* @param posicao Posição do cabeçalho a ser removido
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
* @param posicao Posição do item a ser removido
* @return Referência para o item removido
**************************************************************************************************/
void removerTabelaItem(Tabela* tabela, int posicao);

/**************************************************************************************************
* Exibe um menu na saída do console
* @param menu Menu a ser exibido
**************************************************************************************************/
void exibirMenu(Menu* menu);

/**************************************************************************************************
* Exibe um formulário na saída do console
* @param formulario Formulário a ser exibido
**************************************************************************************************/
void exibirFormulario(Formulario* formulario);

/**************************************************************************************************
* Exibe uma tabela na saída do console
* @param tabela Tabela a ser exibida
**************************************************************************************************/
void exibirTabela(Tabela* tabela);

/**************************************************************************************************
* Lê uma entrada do console
* @param entrada String para armazenar a entrada
* @param tamanho Tamanho da string de entrada
**************************************************************************************************/
void lerEntrada(char* entrada, int tamanho);

/**************************************************************************************************
* Lê um número inteiro do console
* @param entrada String para armazenar a entrada
* @param tamanho Tamanho da string de entrada
* @return Número inteiro lido ou -1, se a entrada não for válida
**************************************************************************************************/
int lerInteiro(char* entrada, int tamanho);

/**************************************************************************************************
* Converte uma string em um número inteiro
* @param entrada String a ser convertida
* @return Número inteiro convertido ou -1, se a conversão não for possível
**************************************************************************************************/
int converterInteiro(const char* entrada);

/**************************************************************************************************
* Lê um número decimal do console
* @param entrada String para armazenar a entrada
* @param tamanho Tamanho da string de entrada
* @return Número decimal lido ou -1, se a entrada não for válida
**************************************************************************************************/
float lerDecimal(char* entrada, int tamanho);

/**************************************************************************************************
* Converte uma string em um número decimal
* @param entrada String a ser convertida
* @return Número decimal convertido ou -1, se a conversão não for possível
**************************************************************************************************/
float converterDecimal(const char* entrada);

/**************************************************************************************************
* Remove os caracteres excendentes da entrada padrão
**************************************************************************************************/
void limparEntrada();

/**************************************************************************************************
* Limpa a tela do console
**************************************************************************************************/
void limparConsole();
