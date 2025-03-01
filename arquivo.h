#pragma once

#include "sistema.h"

/**************************************************************************************************
* Salva um funcionário no arquivo de funcionários
* @param funcionario Funcionário a ser salvo
**************************************************************************************************/
void salvarFuncionario(Funcionario* funcionario);

/**************************************************************************************************
* Exclui um funcionário do arquivo de funcionários
* @param funcionario Funcionário a ser excluído
**************************************************************************************************/
void removerFuncionario(Funcionario* funcionario);

/**************************************************************************************************
* Carrega uma lista de funcionários a partir do arquivo de funcionários
* @return Lista de funcionários carregada
**************************************************************************************************/
Lista* carregarListaFuncionarios();

/**************************************************************************************************
* Carrega um funcionário a partir do arquivo de funcionários
* @param usuario Usuário do funcionário a ser carregado
* @return Funcionário carregado ou nulo se não encontrado
**************************************************************************************************/
Funcionario* carregarFuncionarioPorUsuario(const char* usuario);

/**************************************************************************************************
* Salva um cliente no arquivo de clientes, atualizando se já existir
* @param cliente Cliente a ser salvo
**************************************************************************************************/
void salvarCliente(Cliente* cliente);

/**************************************************************************************************
* Atualiza um cliente no arquivo de clientes
* @param cliente Cliente a ser atualizado
**************************************************************************************************/
void atualizarCliente(Cliente* cliente);

/**************************************************************************************************
* Exclui um cliente do arquivo de clientes
* @param cliente Cliente a ser excluído
**************************************************************************************************/
void removerCliente(Cliente* cliente);

/**************************************************************************************************
* Carrega uma lista de clientes a partir do arquivo de clientes
* @return Lista de clientes carregada
**************************************************************************************************/
Lista* carregarListaClientes();

/**************************************************************************************************
* Carrega um cliente a partir do arquivo de clientes
* @param cnpj CNPJ do cliente a ser carregado
* @return Cliente carregado ou nulo se não encontrado
**************************************************************************************************/
Cliente* carregarClientePorCNPJ(const char* cnpj);

/**************************************************************************************************
* Gera um novo relatório de clientes no formato CSV
**************************************************************************************************/
void gerarRelatorioClientes();

/**************************************************************************************************
* Gera um novo relatório de fatuamento no formato CSV
* @param cliente Cliente para o qual será gerado o relatório
**************************************************************************************************/
void gerarRelatorioFaturamento();
