#pragma once

#include "sistema.h"

/**************************************************************************************************
* Salva um funcion�rio no arquivo de funcion�rios
* @param funcionario Funcion�rio a ser salvo
**************************************************************************************************/
void salvarFuncionario(Funcionario* funcionario);

/**************************************************************************************************
* Exclui um funcion�rio do arquivo de funcion�rios
* @param funcionario Funcion�rio a ser exclu�do
**************************************************************************************************/
void removerFuncionario(Funcionario* funcionario);

/**************************************************************************************************
* Carrega uma lista de funcion�rios a partir do arquivo de funcion�rios
* @return Lista de funcion�rios carregada
**************************************************************************************************/
Lista* carregarListaFuncionarios();

/**************************************************************************************************
* Carrega um funcion�rio a partir do arquivo de funcion�rios
* @param usuario Usu�rio do funcion�rio a ser carregado
* @return Funcion�rio carregado ou nulo se n�o encontrado
**************************************************************************************************/
Funcionario* carregarFuncionarioPorUsuario(const char* usuario);

/**************************************************************************************************
* Salva um cliente no arquivo de clientes, atualizando se j� existir
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
* @param cliente Cliente a ser exclu�do
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
* @return Cliente carregado ou nulo se n�o encontrado
**************************************************************************************************/
Cliente* carregarClientePorCNPJ(const char* cnpj);

/**************************************************************************************************
* Gera um novo relat�rio de clientes no formato CSV
**************************************************************************************************/
void gerarRelatorioClientes();

/**************************************************************************************************
* Gera um novo relat�rio de fatuamento no formato CSV
* @param cliente Cliente para o qual ser� gerado o relat�rio
**************************************************************************************************/
void gerarRelatorioFaturamento();
