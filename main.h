#pragma once

#include <stdio.h>

#include "arquivo.h"
#include "interface.h"
#include "lista.h"
#include "main.h"
#include "sistema.h"

enum MenuAtual {
	MENU_ACESSO,
	MENU_INICIO,
	MENU_FUNCIONARIOS,
	MENU_CLIENTES,
	MENU_RELATORIOS,
	SAIR
};

int MENU_ATUAL = MENU_ACESSO;

/**************************************************************************************************
* Exibe uma tabela com os clientes cadastrados
**************************************************************************************************/
static void exibirClientes() {
	Lista* clientes = carregarListaClientes();

	TabelaCabecalho* cabecalhoNumeroLinha = criarTabelaCabecalho("No.");
	TabelaCabecalho* cabecalhoCNPJ = criarTabelaCabecalho("CNPJ");
	TabelaCabecalho* cabecalhoNomeFantasia = criarTabelaCabecalho("Nome Fantasia");
	TabelaCabecalho* cabecalhoDataAbertura = criarTabelaCabecalho("Data de Abertura");
	TabelaCabecalho* cabecalhoNome = criarTabelaCabecalho("Nome do Cliente");
	TabelaCabecalho* cabecalhoTelefoneCliente = criarTabelaCabecalho("Telefone do Cliente");
	TabelaCabecalho* cabecalhoEmailCliente = criarTabelaCabecalho("Email do Cliente");
	TabelaCabecalho* cabecalhoCargoCliente = criarTabelaCabecalho("Cargo do Cliente");

	Tabela* tabela = criarTabela();
	adicionarTabelaCabecalho(tabela, cabecalhoNumeroLinha);
	adicionarTabelaCabecalho(tabela, cabecalhoCNPJ);
	adicionarTabelaCabecalho(tabela, cabecalhoNomeFantasia);
	adicionarTabelaCabecalho(tabela, cabecalhoDataAbertura);
	adicionarTabelaCabecalho(tabela, cabecalhoNome);
	adicionarTabelaCabecalho(tabela, cabecalhoTelefoneCliente);
	adicionarTabelaCabecalho(tabela, cabecalhoEmailCliente);
	adicionarTabelaCabecalho(tabela, cabecalhoCargoCliente);

	for (int i = 0; i < clientes->tamanho; i++) {
		char numeroLinha[4];
		sprintf_s(numeroLinha, sizeof(numeroLinha), "%d", i + 1);

		Cliente* cliente = obterElemento(clientes, i);

		TabelaItem* item = criarTabelaItem();
		adicionarColunaTabelaItem(item, numeroLinha);
		adicionarColunaTabelaItem(item, cliente->empresa->cnpj);
		adicionarColunaTabelaItem(item, cliente->empresa->nomeFantasia);
		adicionarColunaTabelaItem(item, cliente->empresa->dataAbertura);
		adicionarColunaTabelaItem(item, cliente->nome);
		adicionarColunaTabelaItem(item, cliente->contato->telefone);
		adicionarColunaTabelaItem(item, cliente->contato->email);
		adicionarColunaTabelaItem(item, cliente->cargo);

		adicionarTabelaItem(tabela, item);
	}

	exibirTabela(tabela);

	liberarTabela(tabela);
	percorrerLista(clientes, liberarListaClientes);
	liberarLista(clientes);
}

/**************************************************************************************************
* Exibe uma tabela com os funcion�rios cadastrados
**************************************************************************************************/
static void exibirFuncionarios() {
	Lista* funcionarios = carregarListaFuncionarios();

	TabelaCabecalho* cabecalhoNumeroLinha = criarTabelaCabecalho("No.");
	TabelaCabecalho* cabecalho = criarTabelaCabecalho("Usuario");

	Tabela* tabela = criarTabela();
	adicionarTabelaCabecalho(tabela, cabecalhoNumeroLinha);
	adicionarTabelaCabecalho(tabela, cabecalho);

	for (int i = 0; i < funcionarios->tamanho; i++) {
		char numeroLinha[4];
		sprintf_s(numeroLinha, sizeof(numeroLinha), "%d", i + 1);

		Funcionario* funcionario = obterElemento(funcionarios, i);

		TabelaItem* item = criarTabelaItem();
		adicionarColunaTabelaItem(item, numeroLinha);
		adicionarColunaTabelaItem(item, funcionario->usuario);
		adicionarTabelaItem(tabela, item);
	}

	exibirTabela(tabela);

	liberarTabela(tabela);
	percorrerLista(funcionarios, liberarListaFuncionarios);
	liberarLista(funcionarios);
}

/**************************************************************************************************
* Exibe uma tabela com os relat�rios do cliente
* @param cliente Cliente vinculado aos relat�rios
**************************************************************************************************/
static void exibirRelatorios(Cliente* cliente) {
	if (cliente == NULL) {
		fprintf(stderr, "Erro ao exibir relatorios: parametro nulo\n");
		exit(2);
	}

	TabelaCabecalho* cabecalhoNumeroLinha = criarTabelaCabecalho("No.");
	TabelaCabecalho* cabecalhoResiduosTratados = criarTabelaCabecalho("Residuos Tratados");
	TabelaCabecalho* cabecalhoValorEstimado = criarTabelaCabecalho("Valor Estimado");
	TabelaCabecalho* cabecalhoData = criarTabelaCabecalho("Data");

	Tabela* tabela = criarTabela();
	adicionarTabelaCabecalho(tabela, cabecalhoNumeroLinha);
	adicionarTabelaCabecalho(tabela, cabecalhoResiduosTratados);
	adicionarTabelaCabecalho(tabela, cabecalhoValorEstimado);
	adicionarTabelaCabecalho(tabela, cabecalhoData);

	for (int i = 0; i < cliente->relatorios->tamanho; i++) {
		Relatorio* relatorio = obterElemento(cliente->relatorios, i);

		char numeroLinha[4];
		char residuosTratados[16];
		char valorEstimado[16];

		sprintf_s(numeroLinha, sizeof(numeroLinha), "%d", i + 1);
		sprintf_s(residuosTratados, sizeof(residuosTratados), "%d KG", relatorio->residuosTratados);
		sprintf_s(valorEstimado, sizeof(valorEstimado), "%.2f R$", relatorio->valorEstimado);

		TabelaItem* item = criarTabelaItem();
		adicionarColunaTabelaItem(item, numeroLinha);
		adicionarColunaTabelaItem(item, residuosTratados);
		adicionarColunaTabelaItem(item, valorEstimado);
		adicionarColunaTabelaItem(item, relatorio->data);

		adicionarTabelaItem(tabela, item);
	}

	exibirTabela(tabela);
	liberarTabela(tabela);
}

/**************************************************************************************************
* Menu acesso - Entrar
* 
* Fun��o de comando para o item de menu "Entrar". Respons�vel por exibir o formul�rio de login e
* autenticar o usu�rio. Em caso de sucesso, exibe uma mensagem de boas-vindas e altera o menu atual
* para o menu principal. Em caso de falha, exibe uma mensagem de erro.
**************************************************************************************************/
void funcaoMenuAcessoEntrar() {
	FormularioItem* formularioUsuario = criarFormularioItem("Usuario", "");
	FormularioItem* formularioSenha = criarFormularioItem("Senha", "");

	Formulario* formulario = criarFormulario("ENTRAR - USUARIO");
	adicionarFormularioItem(formulario, formularioUsuario);
	adicionarFormularioItem(formulario, formularioSenha);

	exibirFormulario(formulario);

	if (formularioUsuario->valorInformado == NULL || formularioSenha->valorInformado == NULL) {
		liberarFormulario(formulario);
		printf("\nUsuario ou senha nao informado\n");
		limparConsole();
		return;
	}

	Funcionario* funcionario = carregarFuncionarioPorUsuario(formularioUsuario->valorInformado);

	if (funcionario == NULL || strcmp(funcionario->senha, formularioSenha->valorInformado) != 0) {
		liberarFormulario(formulario);
		liberarFuncionario(funcionario);
		printf("\nUsuario ou senha nao conferem\n");
		limparConsole();
		return;
	}

	printf("\nEntrou com sucesso, %s!\n", funcionario->usuario);
	MENU_ATUAL = MENU_INICIO;

	liberarFormulario(formulario);
	liberarFuncionario(funcionario);

	limparConsole();
}

/**************************************************************************************************
* Menu acesso - Cadastrar
* 
* Fun��o de comando para o item de menu "Cadastrar". Respons�vel por exibir o formul�rio de 
* cadastro e salvar o novo usu�rio. Em caso de sucesso, exibe uma mensagem de confirma��o e altera
* o menu atual para o menu inicial. Em caso de falha, exibe uma mensagem de erro.
**************************************************************************************************/
void funcaoMenuAcessoCadastrar() {
	FormularioItem* formularioUsuario = criarFormularioItem("Usuario", "");
	FormularioItem* formularioSenha = criarFormularioItem("Senha", "");

	Formulario* formulario = criarFormulario("CADASTRAR - USUARIO");
	adicionarFormularioItem(formulario, formularioUsuario);
	adicionarFormularioItem(formulario, formularioSenha);

	exibirFormulario(formulario);

	if (formularioUsuario->valorInformado == NULL || formularioSenha->valorInformado == NULL) {
		liberarFormulario(formulario);
		printf("\nUsuario ou senha nao informado!\n");
		limparConsole();
		return;
	}

	Funcionario* funcionario = criarFuncionario(formularioUsuario->valorInformado, formularioSenha->valorInformado);
	Funcionario* funcionarioExistente = carregarFuncionarioPorUsuario(funcionario->usuario); 
	
	if (funcionarioExistente != NULL) {
		printf("\nUsuario com nome %s ja existe!\n", funcionario->usuario);
		liberarFormulario(formulario);
		liberarFuncionario(funcionario);
		liberarFuncionario(funcionarioExistente);
		limparConsole();
		return;
	}

	salvarFuncionario(funcionario);
	printf("\nUsuario cadastrado com sucesso!\n");
	MENU_ATUAL = MENU_ACESSO;

	liberarFormulario(formulario);
	liberarFuncionario(funcionario);
	limparConsole();
}

/**************************************************************************************************
* Menu acesso - Sair
* 
* Fun��o de comando para o item de menu "Sair". Respons�vel por exibir uma mensagem de sa�da e
* alterar o menu atual para o menu de sa�da.
**************************************************************************************************/
void funcaoMenuAcessoSair() {
	printf("Saindo do sistema!\n");
	MENU_ATUAL = SAIR;

	limparConsole();
}

/**************************************************************************************************
* Menu in�cio - Voltar
*
* Fun��o de comando para o item de menu "Voltar". Respons�vel por alterar o menu atual para o menu
* de acesso.
**************************************************************************************************/
void funcaoMenuInicioVoltar() {
	MENU_ATUAL = MENU_ACESSO;
}

/**************************************************************************************************
* Menu in�cio - Funcion�rios
*
* Fun��o de comando para o item de menu "Funcion�rios". Respons�vel por alterar o menu atual para o
* menu de funcion�rios.
**************************************************************************************************/
void funcaoMenuInicioFuncionarios() {
	MENU_ATUAL = MENU_FUNCIONARIOS;
}

/**************************************************************************************************
* Menu in�cio - Clientes
* 
* Fun��o de comando para o item de menu "Clientes". Respons�vel por alterar o menu atual para o
* menu de clientes.
**************************************************************************************************/
void funcaoMenuInicioClientes() {
	MENU_ATUAL = MENU_CLIENTES;
}

/**************************************************************************************************
* Menu in�cio - Relat�rios
* 
* Fun��o de comando para o item de menu "Relat�rios". Respons�vel por alterar o menu atual para o
* menu de relat�rios.
**************************************************************************************************/
void funcaoMenuInicioRelatorios() {
	MENU_ATUAL = MENU_RELATORIOS;
}

/**************************************************************************************************
* Menu funcion�rios - Voltar
* 
* Fun��o de comando para o item de menu "Voltar". Respons�vel por alterar o menu atual para o menu
* de in�cio.
**************************************************************************************************/
void funcaoMenuFuncionariosVoltar() {
	MENU_ATUAL = MENU_INICIO;
}

/**************************************************************************************************
* Menu funcion�rios - Consultar
* 
* Fun��o de comando para o item de menu "Consultar". Respons�vel por carregar a lista de funcion�rios
* e exibir em uma tabela.
**************************************************************************************************/
void funcaoMenuFuncionariosConsultar() {
	exibirFuncionarios();

	char entrada[4];
	printf("\nPressione ENTER para continuar...");
	lerEntrada(entrada, sizeof(entrada));
	limparConsole();
}

/**************************************************************************************************
* Menu funcion�rios - Adicionar
* 
* Fun��o de comando para o item de menu "Adicionar". Respons�vel por alterar o menu atual para o
* menu de cadastro de funcion�rios.
**************************************************************************************************/
void funcaoMenuFuncionariosAdicionar() {
	funcaoMenuAcessoCadastrar();
	MENU_ATUAL = MENU_FUNCIONARIOS;
}

/**************************************************************************************************
* Menu funcion�rios - Remover
* 
* Fun��o de comando para o item de menu "Remover". Respons�vel por alterar o menu atual para o menu
* de remo��o de funcion�rios. Em caso de sucesso, exibe uma mensagem de confirma��o. Em caso de
* falha, exibe uma mensagem de erro.
**************************************************************************************************/
void funcaoMenuFuncionariosRemover() {
	exibirFuncionarios();

	Lista* funcionarios = carregarListaFuncionarios();

	char entrada[4];
	printf("No. do funcionario para remover: ");
	int numeroFuncionario = lerInteiro(entrada, sizeof(entrada));

	if (numeroFuncionario < 1 || numeroFuncionario > funcionarios->tamanho) {
		printf("\nFuncionario %d nao encontrado!\n", numeroFuncionario);

		percorrerLista(funcionarios, liberarListaFuncionarios);
		liberarLista(funcionarios);
		limparConsole();
		return;
	}

	Funcionario* funcionario = obterElemento(funcionarios, numeroFuncionario - 1);
	removerFuncionario(funcionario);
	printf("\nFuncionario %d %s removido com sucesso!\n", numeroFuncionario, funcionario->usuario);

	percorrerLista(funcionarios, liberarListaFuncionarios);
	liberarLista(funcionarios);
	limparConsole();
}

/**************************************************************************************************
* Menu clientes - Voltar
* 
* Fun��o de comando para o item de menu "Voltar". Respons�vel por alterar o menu atual para o menu
* de in�cio.
**************************************************************************************************/
void funcaoMenuClientesVoltar() {
	MENU_ATUAL = MENU_INICIO;
}

/**************************************************************************************************
* Menu clientes - Consultar clientes
*
* Fun��o de comando para o item de menu "Consultar clientes". Respons�vel por carregar a lista de
* clientes e exibir em uma tabela.
**************************************************************************************************/
void funcaoMenuClientesConsultar() {
	exibirClientes();

	char entrada[4];
	printf("\nPressione ENTER para continuar...");
	lerEntrada(entrada, sizeof(entrada));
	limparConsole();
}

/**************************************************************************************************
* Menu clientes - Adicionar cliente
*
* Fun��o de comando para o item de menu "Adicionar cliente". Respons�vel por exibir um formul�rio
* de cadastro de cliente e salvar o novo cliente. Em caso de sucesso, exibe uma mensagem de
* confirma��o. Em caso de falha, exibe uma mensagem de erro.
**************************************************************************************************/
void funcaoMenuClientesAdicionar() {
	Formulario* formulario = criarFormulario("ADICIONAR - CLIENTE");

	FormularioItem* formularioNome = criarFormularioItem("Cliente - Nome", "");
	FormularioItem* formularioCargo = criarFormularioItem("Cliente - Cargo", "");
	adicionarFormularioItem(formulario, formularioNome);
	adicionarFormularioItem(formulario, formularioCargo);

	FormularioItem* formularioContatoTelefone = criarFormularioItem("Cliente - Telefone", "");
	FormularioItem* formularioContatoEmail = criarFormularioItem("Cliente - Email", "");
	adicionarFormularioItem(formulario, formularioContatoTelefone);
	adicionarFormularioItem(formulario, formularioContatoEmail);

	FormularioItem* formularioEmpresaCNPJ = criarFormularioItem("Empresa - CNPJ", "");
	FormularioItem* formularioEmpresaRazaoSocial = criarFormularioItem("Empresa - Razao social", "");
	FormularioItem* formularioEmpresaNomeFantasia = criarFormularioItem("Empresa - Nome fantasia", "");
	FormularioItem* formularioEmpresaDataAbertura = criarFormularioItem("Empresa - Data de abertura (DD/MM/AAAA)", "");
	adicionarFormularioItem(formulario, formularioEmpresaCNPJ);
	adicionarFormularioItem(formulario, formularioEmpresaRazaoSocial);
	adicionarFormularioItem(formulario, formularioEmpresaNomeFantasia);
	adicionarFormularioItem(formulario, formularioEmpresaDataAbertura);

	FormularioItem* formularioEnderecoCEP = criarFormularioItem("Endereco empresa - CEP", "");
	FormularioItem* formularioEnderecoEstado = criarFormularioItem("Endereco empresa - Sigla do estado (XX)", "");
	FormularioItem* formularioEnderecoCidade = criarFormularioItem("Endereco empresa - Cidade", "");
	FormularioItem* formularioEnderecoBairro = criarFormularioItem("Endereco empresa - Bairro", "");
	FormularioItem* formularioEnderecoRua = criarFormularioItem("Endereco empresa - Rua", "");
	FormularioItem* formularioEnderecoNumero = criarFormularioItem("Endereco empresa - Numero completo", "");
	FormularioItem* formularioEnderecoRegiao = criarFormularioItem("Endereco empresa - Regiao", "");
	adicionarFormularioItem(formulario, formularioEnderecoCEP);
	adicionarFormularioItem(formulario, formularioEnderecoEstado);
	adicionarFormularioItem(formulario, formularioEnderecoCidade);
	adicionarFormularioItem(formulario, formularioEnderecoBairro);
	adicionarFormularioItem(formulario, formularioEnderecoRua);
	adicionarFormularioItem(formulario, formularioEnderecoNumero);
	adicionarFormularioItem(formulario, formularioEnderecoRegiao);

	FormularioItem* formularioContatoEmpresaTelefone = criarFormularioItem("Contato empresa - Telefone", "");
	FormularioItem* formularioContatoEmpresaEmail = criarFormularioItem("Contato empresa - E-mail", "");
	adicionarFormularioItem(formulario, formularioContatoEmpresaTelefone);
	adicionarFormularioItem(formulario, formularioContatoEmpresaEmail);

	exibirFormulario(formulario);

	if (formularioNome->valorInformado == NULL || formularioCargo->valorInformado == NULL || formularioContatoTelefone->valorInformado == NULL || formularioContatoEmail->valorInformado == NULL || formularioEmpresaCNPJ->valorInformado == NULL || formularioEmpresaRazaoSocial->valorInformado == NULL || formularioEmpresaNomeFantasia->valorInformado == NULL || formularioEmpresaDataAbertura->valorInformado == NULL || formularioEnderecoCEP->valorInformado == NULL || formularioEnderecoEstado->valorInformado == NULL || formularioEnderecoCidade->valorInformado == NULL || formularioEnderecoBairro->valorInformado == NULL || formularioEnderecoRua->valorInformado == NULL || formularioEnderecoNumero->valorInformado == NULL || formularioEnderecoRegiao->valorInformado == NULL || formularioContatoEmpresaTelefone->valorInformado == NULL || formularioContatoEmpresaEmail->valorInformado == NULL ) {
		printf("\nCampo obrigatorio nao informado!\n");
		liberarFormulario(formulario);
		limparConsole();
		return;
	}

	int regiao = converterRegiaoDeString(formularioEnderecoRegiao->valorInformado);

	if (regiao == -1) {
		printf("\nRegiao informada %s nao e valida (NORTE, SUL, LESTE, OESTE)!\n", formularioEnderecoRegiao->valorInformado);
		liberarFormulario(formulario);
		limparConsole();
		return;
	}

	Contato* contatoEmpresa = criarContato(formularioContatoEmpresaTelefone->valorInformado, formularioContatoEmpresaEmail->valorInformado);
	Endereco* enderecoEmpresa = criarEndereco(formularioEnderecoCEP->valorInformado, formularioEnderecoEstado->valorInformado, formularioEnderecoCidade->valorInformado, formularioEnderecoBairro->valorInformado, formularioEnderecoRua->valorInformado, formularioEnderecoNumero->valorInformado, regiao);
	Empresa* empresa = criarEmpresa(formularioEmpresaCNPJ->valorInformado, formularioEmpresaRazaoSocial->valorInformado, formularioEmpresaNomeFantasia->valorInformado, formularioEmpresaDataAbertura->valorInformado, enderecoEmpresa, contatoEmpresa);

	Contato* contatoCliente = criarContato(formularioContatoTelefone->valorInformado, formularioContatoEmail->valorInformado);
	Cliente* cliente = criarCliente(formularioNome->valorInformado, formularioCargo->valorInformado, contatoCliente, empresa);
	Cliente* clienteExistente = carregarClientePorCNPJ(cliente->empresa->cnpj);

	if (clienteExistente != NULL) {
		printf("\nCliente com o CNPJ %s ja existe!\n", cliente->empresa->cnpj);
		liberarFormulario(formulario);
		liberarCliente(cliente);
		liberarCliente(clienteExistente);
		limparConsole();
		return;
	}

	salvarCliente(cliente);
	fprintf(stderr, "\nCliente adicionado com sucesso!\n");
	MENU_ATUAL = MENU_CLIENTES;

	liberarCliente(cliente);
	liberarFormulario(formulario);
	limparConsole();
}

/**************************************************************************************************
* Menu clientes - Remover
* 
* Fun��o de comando para o item de menu "Remover". Respons�vel por carregar a lista de clientes e
* exibir em uma tabela. Em caso de sucesso, exibe uma mensagem de confirma��o. Em caso de falha,
* exibe uma mensagem de erro.
**************************************************************************************************/
void funcaoMenuClientesRemover() {
	exibirClientes();

	Lista* clientes = carregarListaClientes();

	char entrada[4];
	printf("\nNo. do cliente para remover: ");
	int numeroCliente = lerInteiro(entrada, sizeof(entrada));

	if (numeroCliente < 1 || numeroCliente > clientes->tamanho) {
		printf("Cliente No. %d nao encontrado!\n", numeroCliente);

		percorrerLista(clientes, liberarListaClientes);
		liberarLista(clientes);
		limparConsole();
		return;
	}

	Cliente* cliente = obterElemento(clientes, numeroCliente - 1);
	removerCliente(cliente);
	printf("Cliente No. %d %s removido com sucesso!\n", numeroCliente, cliente->nome);

	percorrerLista(clientes, liberarListaClientes);
	liberarLista(clientes);
	limparConsole();
}

/**************************************************************************************************
* Menu clientes - Consultar relat�rios
* 
* Fun��o de comando para o item de menu "Consultar relat�rios". Respons�vel por carregar a lista de
* relat�rios de um cliente e exibir em uma tabela.
**************************************************************************************************/
void funcaoMenuClientesConsultarRelatorios() {
	exibirClientes();

	Lista* clientes = carregarListaClientes();

	char entrada[4];
	printf("\nNo. do cliente para consultar relatorios: ");
	int numeroCliente = lerInteiro(entrada, sizeof(entrada));

	if (numeroCliente < 1 || numeroCliente > clientes->tamanho) {
		printf("Cliente No. %d nao encontrado!\n", numeroCliente);

		percorrerLista(clientes, liberarListaClientes);
		liberarLista(clientes);
		limparConsole();
		return;
	}

	limparConsole();

	Cliente* cliente = obterElemento(clientes, numeroCliente - 1);
	exibirRelatorios(cliente);

	char entradaRelatorio[4];
	printf("\nPressione ENTER para continuar...");
	lerEntrada(entradaRelatorio, sizeof(entradaRelatorio));

	percorrerLista(clientes, liberarListaClientes);
	liberarLista(clientes);
	limparConsole();
}

/**************************************************************************************************
* Menu clientes - Adicionar relat�rio
* 
* Fun��o de comando para o item de menu "Adicionar relat�rio". Respons�vel por apresentar um
* formul�rio de cadastro de relat�rio e vincular ao cliente.
**************************************************************************************************/
void funcaoMenuClientesAdicionarRelatorio() {
	exibirClientes();

	Lista* clientes = carregarListaClientes();

	char entrada[4];
	printf("\nNo. do cliente para vincular o relatorio: ");
	int numeroCliente = lerInteiro(entrada, sizeof(entrada));

	if (numeroCliente < 1 || numeroCliente > clientes->tamanho) {
		printf("Cliente No. %d nao encontrado!\n", numeroCliente);

		percorrerLista(clientes, liberarListaClientes);
		liberarLista(clientes);
		limparConsole();
		return;
	}

	limparConsole();

	FormularioItem* formularioResiduosTratados = criarFormularioItem("Residuos Tratados (KG)", "");
	FormularioItem* formularioValorEstimado = criarFormularioItem("Valor Estimado (R$)", "");
	FormularioItem* formularioData = criarFormularioItem("Data (DD/MM/AAAA)", "");

	Formulario* formulario = criarFormulario("ADICIONAR - RELATORIO");
	adicionarFormularioItem(formulario, formularioResiduosTratados);
	adicionarFormularioItem(formulario, formularioValorEstimado);
	adicionarFormularioItem(formulario, formularioData);

	exibirFormulario(formulario);

	if (formularioResiduosTratados->valorInformado == NULL || formularioValorEstimado->valorInformado == NULL || formularioData->valorInformado == NULL) {
		printf("Campo obrigatorio nao informado!\n");

		liberarFormulario(formulario);
		percorrerLista(clientes, liberarListaClientes);
		liberarLista(clientes);
		limparConsole();
		return;
	}

	int residuosTratados = converterInteiro(formularioResiduosTratados->valorInformado);
	float valorEstimado = converterDecimal(formularioValorEstimado->valorInformado);

	if (residuosTratados == -1 || valorEstimado == -1) {
		printf("Residuos tratados ou valor estimado nao e um numero valido!\n");

		liberarFormulario(formulario);
		percorrerLista(clientes, liberarListaClientes);
		liberarLista(clientes);
		limparConsole();
		return;
	}

	Relatorio* relatorio = criarRelatorio(residuosTratados, valorEstimado, formularioData->valorInformado);
	Cliente* cliente = obterElemento(clientes, numeroCliente - 1);
	adicionarRelatorio(cliente, relatorio);
	atualizarCliente(cliente);

	printf("Relatorio adicionado com sucesso!\n");

	liberarFormulario(formulario);
	percorrerLista(clientes, liberarListaClientes);
	liberarLista(clientes);
	limparConsole();
}

/**************************************************************************************************
* Menu clientes - Remover relat�rio
* 
* Fun��o de comando para o item de menu "Remover relat�rio". Respons�vel por remover um relat�rio
* vinculado a um cliente.
**************************************************************************************************/
void funcaoMenuClientesRemoverRelatorio() {
	exibirClientes();

	Lista* clientes = carregarListaClientes();

	char entrada[4];
	printf("\nNo. do cliente para remover relatorio: ");
	int numeroCliente = lerInteiro(entrada, sizeof(entrada));

	if (numeroCliente < 1 || numeroCliente > clientes->tamanho) {
		printf("Cliente No. %d nao encontrado!\n", numeroCliente);

		percorrerLista(clientes, liberarListaClientes);
		liberarLista(clientes);
		limparConsole();
		return;
	}

	limparConsole();
	Cliente* cliente = obterElemento(clientes, numeroCliente - 1);
	exibirRelatorios(cliente);

	char entradaRelatorio[4];
	printf("\nNo. do relatorio para remover: ");
	int numeroRelatorio = lerInteiro(entradaRelatorio, sizeof(entradaRelatorio));

	if (numeroRelatorio < 1 || numeroRelatorio > cliente->relatorios->tamanho) {
		printf("Relatorio No. %d nao encontrado!\n", numeroRelatorio);

		percorrerLista(clientes, liberarListaClientes);
		liberarLista(clientes);
		limparConsole();
		return;
	}

	Relatorio* relatorio = obterElemento(cliente->relatorios, numeroRelatorio - 1);
	removerRelatorio(cliente, numeroRelatorio - 1);
	atualizarCliente(cliente);
	liberarRelatorio(relatorio);

	printf("Relatorio No. %d removido com sucesso!\n", numeroRelatorio);

	percorrerLista(clientes, liberarListaClientes);
	liberarLista(clientes);
	limparConsole();
}

/**************************************************************************************************
* Menu relat�rios - Voltar
* 
* Fun��o de comando para o item de menu "Voltar". Respons�vel por alterar o menu atual para o menu
* de in�cio.
**************************************************************************************************/
void funcaoMenuRelatoriosVoltar() {
	MENU_ATUAL = MENU_INICIO;
}

/**************************************************************************************************
* Menu relat�rios - Faturamento
* 
* Fun��o de comando para o item de menu "Faturamento". Respons�vel por gerar um relat�rio de
* faturamento.
**************************************************************************************************/
void funcaoMenuRelatoriosFaturamento() {
	gerarRelatorioFaturamento();
	printf("Relatorio de faturamento gerado com sucesso!\n");
	MENU_ATUAL = MENU_RELATORIOS;
	limparConsole();
}

/**************************************************************************************************
* Menu relat�rios - Clientes
* 
* Fun��o de comando para o item de menu "Clientes". Respons�vel por gerar um relat�rio de clientes.
**************************************************************************************************/
void funcaoMenuRelatoriosClientes() {
	gerarRelatorioClientes();
	printf("Relatorio de clientes gerado com sucesso!\n");
	MENU_ATUAL = MENU_RELATORIOS;
	limparConsole();
}
