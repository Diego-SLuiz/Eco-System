#include "main.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	/**************************************************************************************************
	* Menu acesso
	**************************************************************************************************/
	Menu* menuAcesso = criarMenu("MENU - ACESSO");

	MenuItem* menuAcessoEntrar = criarMenuItem("Entrar", funcaoMenuAcessoEntrar);
	MenuItem* menuAcessoCadastrar = criarMenuItem("Cadastrar", funcaoMenuAcessoCadastrar);
	MenuItem* menuAcessoSair = criarMenuItem("Sair", funcaoMenuAcessoSair);
	
	adicionarMenuItem(menuAcesso, menuAcessoEntrar);
	adicionarMenuItem(menuAcesso, menuAcessoCadastrar);
	adicionarMenuItem(menuAcesso, menuAcessoSair);

	/**************************************************************************************************
	* Menu inicio
	**************************************************************************************************/
	Menu* menuInicio = criarMenu("MENU - INICIO");

	MenuItem* menuInicioVoltar = criarMenuItem("Voltar", funcaoMenuInicioVoltar);
	MenuItem* menuInicioFuncionarios = criarMenuItem("Funcionarios", funcaoMenuInicioFuncionarios);
	MenuItem* menuInicioClientes = criarMenuItem("Clientes", funcaoMenuInicioClientes);
	MenuItem* menuInicioRelatorios = criarMenuItem("Relatorios", funcaoMenuInicioRelatorios);

	adicionarMenuItem(menuInicio, menuInicioVoltar);
	adicionarMenuItem(menuInicio, menuInicioFuncionarios);
	adicionarMenuItem(menuInicio, menuInicioClientes);
	adicionarMenuItem(menuInicio, menuInicioRelatorios);

	/**************************************************************************************************
	* Menu funcionários
	**************************************************************************************************/
	Menu* menuFuncionarios = criarMenu("MENU - FUNCIONARIOS");

	MenuItem* menuFuncionariosVoltar = criarMenuItem("Voltar", funcaoMenuFuncionariosVoltar);
	MenuItem* menuFuncionariosConsultar = criarMenuItem("Consultar funcionarios", funcaoMenuFuncionariosConsultar);
	MenuItem* menuFuncionariosAdicionar = criarMenuItem("Adicionar funcionario", funcaoMenuFuncionariosAdicionar);
	MenuItem* menuFuncionariosRemover = criarMenuItem("Remover funcionario", funcaoMenuFuncionariosRemover);
	
	adicionarMenuItem(menuFuncionarios, menuFuncionariosVoltar);
	adicionarMenuItem(menuFuncionarios, menuFuncionariosConsultar);
	adicionarMenuItem(menuFuncionarios, menuFuncionariosAdicionar);
	adicionarMenuItem(menuFuncionarios, menuFuncionariosRemover);

	/**************************************************************************************************
	* Menu clientes
	**************************************************************************************************/
	Menu* menuClientes= criarMenu("MENU - CLIENTES");

	MenuItem* menuClientesVoltar = criarMenuItem("Voltar", funcaoMenuClientesVoltar);
	MenuItem* menuClientesConsultar = criarMenuItem("Consultar clientes", funcaoMenuClientesConsultar);
	MenuItem* menuClientesAdicionar = criarMenuItem("Adicionar cliente", funcaoMenuClientesAdicionar);
	MenuItem* menuClientesRemover = criarMenuItem("Remover cliente", funcaoMenuClientesRemover);
	MenuItem* menuClientesConsultarRelatorios = criarMenuItem("Consultar relatorios", funcaoMenuClientesConsultarRelatorios);
	MenuItem* menuClientesAdicionarRelatorio = criarMenuItem("Adicionar relatorio", funcaoMenuClientesAdicionarRelatorio);
	MenuItem* menuClientesRemoverRelatorio = criarMenuItem("Remover relatorio", funcaoMenuClientesRemoverRelatorio);

	adicionarMenuItem(menuClientes, menuClientesVoltar);
	adicionarMenuItem(menuClientes, menuClientesConsultar);
	adicionarMenuItem(menuClientes, menuClientesAdicionar);
	adicionarMenuItem(menuClientes, menuClientesRemover);
	adicionarMenuItem(menuClientes, menuClientesConsultarRelatorios);
	adicionarMenuItem(menuClientes, menuClientesAdicionarRelatorio);
	adicionarMenuItem(menuClientes, menuClientesRemoverRelatorio);

	/**************************************************************************************************
	* Menu relatórios
	**************************************************************************************************/
	Menu* menuRelatorios = criarMenu("MENU - RELATORIOS");

	MenuItem* menuRelatoriosVoltar = criarMenuItem("Voltar", funcaoMenuRelatoriosVoltar);
	MenuItem* menuRelatoriosFaturamento = criarMenuItem("Gerar relatorio de Servicos", funcaoMenuRelatoriosFaturamento);
	MenuItem* menuRelatoriosClientes = criarMenuItem("Gerar relatorio de Clientes", funcaoMenuRelatoriosClientes);

	adicionarMenuItem(menuRelatorios, menuRelatoriosVoltar);
	adicionarMenuItem(menuRelatorios, menuRelatoriosFaturamento);
	adicionarMenuItem(menuRelatorios, menuRelatoriosClientes);

	/**************************************************************************************************
	* Execução principal do sistema
	**************************************************************************************************/
	while (MENU_ATUAL != SAIR) {
		switch (MENU_ATUAL) {
		case MENU_ACESSO:
			exibirMenu(menuAcesso);
			break;
		case MENU_INICIO:
			exibirMenu(menuInicio);
			break;
		case MENU_FUNCIONARIOS:
			exibirMenu(menuFuncionarios);
			break;
		case MENU_CLIENTES:
			exibirMenu(menuClientes);
			break;
		case MENU_RELATORIOS:
			exibirMenu(menuRelatorios);
			break;
		}
	}

	/**************************************************************************************************
	* Execução de saída do sistema
	**************************************************************************************************/
	liberarMenu(menuAcesso);
	liberarMenu(menuInicio);
	liberarMenu(menuFuncionarios);
	liberarMenu(menuClientes);
	liberarMenu(menuRelatorios);

	_CrtDumpMemoryLeaks();
	return 0;
}
