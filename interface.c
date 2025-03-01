#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "interface.h"
#include "lista.h"
#include "memoria.h"

MenuItem* criarMenuItem(const char* descricao, void (*comando)()) {
	MenuItem* menuItem = alocarMemoria(sizeof(MenuItem));
	menuItem->descricao = duplicarString(descricao);
	menuItem->comando = comando;

	return menuItem;
}

void liberarMenuItem(MenuItem* menuItem) {
	liberarMemoria(&menuItem->descricao);
	liberarMemoria(&menuItem);
}

void liberarListaMenuItem(void* elemento, int posicao) {
	if (elemento != NULL) {
		MenuItem* menuItem = elemento;
		liberarMenuItem(elemento);
	}
}

Menu* criarMenu(const char* titulo) {
	Menu* menu = alocarMemoria(sizeof(Menu));
	menu->titulo = duplicarString(titulo);
	menu->itens = criarLista();

	return menu;
}

void liberarMenu(Menu* menu) {
	liberarMemoria(&menu->titulo);
	percorrerLista(menu->itens, liberarListaMenuItem);
	liberarLista(menu->itens);
	liberarMemoria(&menu);
}

void liberarListaMenu(void* elemento, int posicao) {
	if (elemento != NULL) {
		Menu* menu = elemento;
		liberarMenu(menu);
	}	
}

void adicionarMenuItem(Menu* menu, MenuItem* item) {
	if (menu == NULL || item == NULL) {
		fprintf(stderr, "Erro ao adicionar item ao menu: parametros nulos\n");
		exit(2);
	}

	adicionarElemento(menu->itens, item);
}

void removerMenuItem(Menu* menu, int posicao) {
	if (menu == NULL) {
		fprintf(stderr, "Erro ao remover item do menu: parametro nulo\n");
		exit(2);
	}

	removerElemento(menu->itens, posicao);
}

FormularioItem* criarFormularioItem(const char* campo, const char* valorPadrao) {
	FormularioItem* formularioItem = alocarMemoria(sizeof(FormularioItem));
	formularioItem->campo = duplicarString(campo);
	formularioItem->valorPadrao = duplicarString(valorPadrao);
	formularioItem->valorInformado = NULL;

	return formularioItem;
}

void liberarFormularioItem(FormularioItem* formularioItem) {
	liberarMemoria(&formularioItem->campo);
	liberarMemoria(&formularioItem->valorPadrao);
	liberarMemoria(&formularioItem->valorInformado);
	liberarMemoria(&formularioItem);
}

void liberarListaFormularioItem(void* elemento, int posicao) {
	if (elemento != NULL) {
		FormularioItem* formularioItem = elemento;
		liberarFormularioItem(formularioItem);
	}
}

Formulario* criarFormulario(const char* titulo) {
	Formulario* formulario = alocarMemoria(sizeof(Formulario));
	formulario->titulo = duplicarString(titulo);
	formulario->itens = criarLista();

	return formulario;
}

void liberarFormulario(Formulario* formulario) {
	liberarMemoria(&formulario->titulo);
	percorrerLista(formulario->itens, liberarListaFormularioItem);
	liberarLista(formulario->itens);
	liberarMemoria(&formulario);
}

void liberarListaFormulario(void* elemento, int posicao) {
	if (elemento != NULL) {
		Formulario* formulario = elemento;
		liberarFormulario(formulario);
	}
}

void adicionarFormularioItem(Formulario* formulario, FormularioItem* item) {
	if (formulario == NULL || item == NULL) {
		fprintf(stderr, "Erro ao adicionar item ao formulario: parametros nulos\n");
		exit(2);
	}

	adicionarElemento(formulario->itens, item);
}

void removerFormularioItem(Formulario* formulario, int posicao) {
	if (formulario == NULL) {
		fprintf(stderr, "Erro ao remover item do formulario: parametro nulo\n");
		exit(2);
	}

	removerElemento(formulario->itens, posicao);
}

TabelaItem* criarTabelaItem() {
	TabelaItem* tabelaItem = alocarMemoria(sizeof(TabelaItem));
	tabelaItem->colunas = criarLista();

	return tabelaItem;
}

void liberarTabelaItem(TabelaItem* tabelaItem) {
	percorrerLista(tabelaItem->colunas, liberarListaElementos);
	liberarLista(tabelaItem->colunas);

	liberarMemoria(&tabelaItem);
}

void liberarListaTabelaItem(void* elemento, int posicao) {
	if (elemento != NULL) {
		TabelaItem* tabelaItem = elemento;
		liberarTabelaItem(tabelaItem);
	}
}

void adicionarColunaTabelaItem(TabelaItem* tabelaItem, const char* valor) {
	if (tabelaItem == NULL || valor == NULL) {
		fprintf(stderr, "Erro ao adicionar coluna a tabela: parametros nulos\n");
		exit(2);
	}

	adicionarElemento(tabelaItem->colunas, duplicarString(valor));
}

void removerColunaTabelaItem(TabelaItem* tabelaItem, int posicao) {
	if (tabelaItem == NULL) {
		fprintf(stderr, "Erro ao remover coluna da tabela: parametro nulo\n");
		exit(2);
	}

	removerElemento(tabelaItem->colunas, posicao);
}

TabelaCabecalho* criarTabelaCabecalho(const char* titulo) {
	if (titulo == NULL) {
		fprintf(stderr, "Erro ao criar cabecalho da tabela: parametro nulo\n");
		exit(2);
	}

	TabelaCabecalho* tabelaCabecalho = alocarMemoria(sizeof(TabelaCabecalho));

	tabelaCabecalho->titulo = duplicarString(titulo);
	tabelaCabecalho->largura = strlen(titulo);

	return tabelaCabecalho;
}

void liberarTabelaCabecalho(TabelaCabecalho* tabelaCabecalho) {
	liberarMemoria(&tabelaCabecalho->titulo);
	liberarMemoria(&tabelaCabecalho);
}

void liberarListaTabelaCabecalho(void* elemento, int posicao) {
	if (elemento != NULL) {
		TabelaCabecalho* tabelaCabecalho = elemento;
		liberarTabelaCabecalho(tabelaCabecalho);
	}
}

Tabela* criarTabela() {
	Tabela* tabela = alocarMemoria(sizeof(Tabela));
	tabela->cabecalho = criarLista();
	tabela->itens = criarLista();

	return tabela;
}

void liberarTabela(Tabela* tabela) {
	percorrerLista(tabela->cabecalho, liberarListaTabelaCabecalho);
	liberarLista(tabela->cabecalho);

	percorrerLista(tabela->itens, liberarListaTabelaItem);
	liberarLista(tabela->itens);

	liberarMemoria(&tabela);
}

void liberarListaTabela(void* elemento, int posicao) {
	if (elemento != NULL) {
		Tabela* tabela = elemento;
		liberarTabela(tabela);
	}
}

void adicionarTabelaCabecalho(Tabela* tabela, TabelaCabecalho* tabelaCabecalho) {
	if (tabela == NULL || tabelaCabecalho == NULL) {
		fprintf(stderr, "Erro ao adicionar coluna a tabela: parametros nulos\n");
		exit(2);
	}

	adicionarElemento(tabela->cabecalho, tabelaCabecalho);

	for (int i = 0; i < tabela->itens->tamanho; i++) {
		TabelaItem* tabelaItem = obterElemento(tabela->itens, i);
		adicionarColunaTabelaItem(tabelaItem, "");
	}
}

void removerTabelaCabecalho(Tabela* tabela, int posicao) {
	if (tabela == NULL) {
		fprintf(stderr, "Erro ao remover coluna da tabela: parametro nulo\n");
		exit(2);
	}

	removerElemento(tabela->cabecalho, posicao);
	
	for (int i = 0; i < tabela->itens->tamanho; i++) {
		TabelaItem* tabelaItem = obterElemento(tabela->itens, i);
		removerColunaTabelaItem(tabelaItem, posicao);
	}
}

void adicionarTabelaItem(Tabela* tabela, TabelaItem* tabelaItem) {
	if (tabela == NULL || tabelaItem == NULL) {
		fprintf(stderr, "Erro ao adicionar item a tabela: parametros nulos\n");
		exit(2);
	}

	if (tabela->cabecalho->tamanho != tabelaItem->colunas->tamanho) {
		fprintf(stderr, "Erro ao adicionar item a tabela: quantidade de colunas incompativel\n");
		exit(3);
	}

	for (int i = 0; i < tabelaItem->colunas->tamanho; i++) {
		TabelaCabecalho* tabelaCabecalho = obterElemento(tabela->cabecalho, i);
		int novoTamanhoColuna = strlen(obterElemento(tabelaItem->colunas, i));

		if (novoTamanhoColuna > tabelaCabecalho->largura) {
			tabelaCabecalho->largura = novoTamanhoColuna;
		}		
	}



	adicionarElemento(tabela->itens, tabelaItem);
}

void removerTabelaItem(Tabela* tabela, int posicao) {
	if (tabela == NULL) {
		fprintf(stderr, "Erro ao remover item da tabela: parametro nulo\n");
		exit(2);
	}

	removerElemento(tabela->itens, posicao);
}

void exibirMenu(Menu* menu) {
	if (menu == NULL) {
		fprintf(stderr, "Erro ao exibir menu: parametro nulo\n");
		exit(2);
	}

	printf("%s\n", menu->titulo);
	
	for (int i = 0; i < menu->itens->tamanho; i++) {
		MenuItem* item = obterElemento(menu->itens, i);
		printf("%d. %s\n", i + 1, item->descricao);
	}

	printf("\nDigite o numero da opcao desejada: ");
	char entradaOpcao[16];
	int opcao = lerInteiro(entradaOpcao, sizeof(entradaOpcao));

	if (opcao <= 0 || opcao > menu->itens->tamanho) {
		limparConsole();
		exibirMenu(menu);
	}
	else {
		MenuItem* menuItemOpcao = obterElemento(menu->itens, opcao - 1);
		printf("Opcao escolhida: %s\n", menuItemOpcao->descricao);
		limparConsole();

		menuItemOpcao->comando();
	}
}

void exibirFormulario(Formulario* formulario) {
	if (formulario == NULL) {
		fprintf(stderr, "Erro ao exibir formulario: parametro nulo\n");
		exit(2);
	}

	printf("%s\n", formulario->titulo);

	for (int i = 0; i < formulario->itens->tamanho; i++) {
		char valorInformado[256];

		FormularioItem* formularioItem = obterElemento(formulario->itens, i);
		printf("%s: ", formularioItem->campo);
		lerEntrada(valorInformado, sizeof(valorInformado));

		if (strlen(valorInformado) > 0) {
			formularioItem->valorInformado = duplicarString(valorInformado);
		}
		else {
			formularioItem->valorInformado = NULL;
		}
	}
}

void exibirTabela(Tabela* tabela) {
	if (tabela == NULL) {
		fprintf(stderr, "Erro ao exibir tabela: parametro nulo\n");
		exit(2);
	}

	for (int i = 0; i < tabela->cabecalho->tamanho; i++) {
		TabelaCabecalho* tabelaCabecalho = obterElemento(tabela->cabecalho, i);
		printf("|%-*s", tabelaCabecalho->largura, tabelaCabecalho->titulo);
	}
	if (tabela->cabecalho->tamanho > 0) {
		printf("|\n");
	}

	for (int linha = 0; linha < tabela->itens->tamanho; linha++) {
		TabelaItem* tabelaItem = obterElemento(tabela->itens, linha);

		for (int coluna = 0; coluna < tabelaItem->colunas->tamanho; coluna++) {
			TabelaCabecalho* tabelaCabecalho = obterElemento(tabela->cabecalho, coluna);
			char* valorColuna = obterElemento(tabelaItem->colunas, coluna);
			
			printf("|%-*s", tabelaCabecalho->largura, valorColuna);
		}
		if (tabelaItem->colunas->tamanho > 0) {
			printf("|\n");
		}
	}
}

void lerEntrada(char* entrada, int tamanho) {
	if (entrada == NULL) {
		fprintf(stderr, "Erro ao ler entrada: parametros nulos ou invalidos\n");
		exit(2);
	}

	if (fgets(entrada, tamanho, stdin) == NULL) {
		fprintf(stderr, "Erro ao ler entrada: entrada invalida\n");
		exit(2);
	}

	size_t tamanhoEntrada = strlen(entrada);

	if (tamanhoEntrada > 0 && entrada[tamanhoEntrada - 1] == '\n') {
		entrada[tamanhoEntrada - 1] = '\0';
	}
	else {
		limparEntrada();
	}
}

int lerInteiro(char* entrada, int tamanho) {
	if (entrada == NULL) {
		fprintf(stderr, "Erro ao ler inteiro: parametros nulos\n");
		exit(2);
	}

	lerEntrada(entrada, tamanho);

	for (int i = 0, tamanhoEntrada = strlen(entrada); i < tamanhoEntrada; i++) {
		if (!isdigit(entrada[i])) {
			return -1;
		}
	}

	int resultado = atoi(entrada);
	return resultado;
}

int converterInteiro(const char* entrada) {
	if (entrada == NULL) {
		fprintf(stderr, "Erro ao converter inteiro: parametro nulo\n");
		exit(2);
	}

	for (int i = 0, tamanhoEntrada = strlen(entrada); i < tamanhoEntrada; i++) {
		if (!isdigit(entrada[i])) {
			return -1;
		}
	}

	int resultado = atoi(entrada);
	return resultado;
}

float lerDecimal(char* entrada, int tamanho) {
	if (entrada == NULL) {
		fprintf(stderr, "Erro ao ler decimal: parametros nulos\n");
		exit(2);
	}

	lerEntrada(entrada, tamanho);
	int casaDecimal = 0;

	for (int i = 0, tamanhoEntrada = strlen(entrada); i < tamanhoEntrada; i++) {
		if (entrada[i] == '.') {
			if (casaDecimal >= 1) {
				return -1;
			}

			casaDecimal++;
			continue;
		}

		if (!isdigit(entrada[i]) || casaDecimal > 1) {
			return -1;
		}
	}

	float resultado = atof(entrada);
	return resultado;
}

float converterDecimal(const char* entrada) {
	if (entrada == NULL) {
		fprintf(stderr, "Erro ao converter decimal: parametro nulo\n");
		exit(2);
	}

	int casaDecimal = 0;

	for (int i = 0, tamanhoEntrada = strlen(entrada); i < tamanhoEntrada; i++) {
		if (entrada[i] == '.') {
			if (casaDecimal >= 1) {
				return -1;
			}

			casaDecimal++;
			continue;
		}

		if (!isdigit(entrada[i]) || casaDecimal > 1) {
			return -1;
		}
	}

	float resultado = atof(entrada);
	return resultado;
}

void limparEntrada() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

void limparConsole() {
	Sleep(1000);
	system("cls || clear");
}
