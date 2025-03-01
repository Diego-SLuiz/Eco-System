#pragma once

#include "lista.h"

typedef enum {
	NORTE,
	SUL,
	LESTE,
	OESTE,
} Regiao;

typedef struct {
	int residuosTratados;
	float valorEstimado;
	char* data;
} Relatorio;

typedef struct {
	char* usuario;
	char* senha;
} Funcionario;

typedef struct {
	char* telefone;
	char* email;
} Contato;

typedef struct {
	char* cep;
	char* estado;
	char* cidade;
	char* bairro;
	char* rua;
	char* numero;
	Regiao regiao;
} Endereco;

typedef struct {
	char* cnpj;
	char* razaoSocial;
	char* nomeFantasia;
	char* dataAbertura;
	Endereco* endereco;
	Contato* contato;
} Empresa;

typedef struct {
	char* nome;
	char* cargo;
	Contato* contato;
	Empresa* empresa;
	Lista* relatorios;
} Cliente;

/**************************************************************************************************
* Cria um novo relat�rio e inicializa seus atributos
* @param residuosTratados Quantidade de res�duos tratados em KG
* @param valorEstimado Valor estimado em R$
* @param data Data de emiss�o do relat�rio no formato MM/AAAA
* @return Refer�ncia para o relat�rio criado
**************************************************************************************************/
Relatorio* criarRelatorio(int residuosTratados, float valorEstimado, const char* data);

/**************************************************************************************************
* Adiciona um relat�rio � lista de relat�rios de um cliente
* @param cliente Cliente a ser associado ao relat�rio
* @param relatorio Relat�rio a ser adicionado
**************************************************************************************************/
void adicionarRelatorio(Cliente* cliente, Relatorio* relatorio);

/**************************************************************************************************
* Remove um relat�rio da lista de relat�rios de um cliente
* @param cliente Cliente a ser desassociado do relat�rio
* @param posicao Posi��o de ocorr�ncia na lista de relat�rios
**************************************************************************************************/
void removerRelatorio(Cliente* cliente, int posicao);

/**************************************************************************************************
* Libera a mem�ria utilizada por um relat�rio e anula a refer�ncia
* @param relatorio Refer�ncia para o relat�rio
**************************************************************************************************/
void liberarRelatorio(Relatorio* relatorio);

/**************************************************************************************************
* Libera a mem�ria utilizada por elementos de uma lista de relat�rios
* @param elemento Elemento a ser liberado
* @param posicao Posi��o de ocorr�ncia na lista
**************************************************************************************************/
void liberarListaRelatorios(void* elemento, int posicao);

/**************************************************************************************************
* Cria um novo funcion�rio e inicializa seus atributos
* @param usuario Nome de usu�rio do funcion�rio
* @param senha Senha de acesso do funcion�rio
* @return Refer�ncia para o funcion�rio criado
**************************************************************************************************/
Funcionario* criarFuncionario(const char* usuario, const char* senha);

/**************************************************************************************************
* Libera a mem�ria utilizada por um funcion�rio e anula a refer�ncia
* @param funcionario Refer�ncia para o funcion�rio
**************************************************************************************************/
void liberarFuncionario(Funcionario* funcionario);

/**************************************************************************************************
* Libera a mem�ria utilizada por elementos de uma lista de funcion�rios
* @param elemento Elemento a ser liberado
* @param posicao Posi��o de ocorr�ncia na lista
**************************************************************************************************/
void liberarListaFuncionarios(void* elemento, int posicao);

/**************************************************************************************************
* Cria um novo contato e inicializa seus atributos
* @param telefone N�mero de telefone do contato no formato (XX) XXXXX-XXXX
* @param email Endere�o de e-mail do contato
* @return Refer�ncia para o contato criado
**************************************************************************************************/
Contato* criarContato(const char* telefone, const char* email);

/**************************************************************************************************
* Libera a mem�ria utilizada por um contato e anula a refer�ncia
* @param contato Refer�ncia para o contato
**************************************************************************************************/
void liberarContato(Contato* contato);

/**************************************************************************************************
* Libera a mem�ria utilizada por elementos de uma lista de contatos
* @param elemento Elemento a ser liberado
* @param posicao Posi��o de ocorr�ncia na lista
**************************************************************************************************/
void liberarListaContatos(void* elemento, int posicao);

/**************************************************************************************************
* Cria um novo endere�o e inicializa seus atributos
* @param cep CEP do endere�o no formato XXXXX-XXX
* @param estado Sigla do estado do endere�o no formato XX
* @param cidade Nome da cidade do endere�o
* @param bairro Nome do bairro do endere�o
* @param rua Nome da rua do endere�o
* @param numero N�mero do endere�o
* @param regiao Regi�o do endere�o
* @return Refer�ncia para o endere�o criado
**************************************************************************************************/
Endereco* criarEndereco(const char* cep, const char* estado, const char* cidade, const char* bairro, const char* rua, const char* numero, Regiao regiao);

/**************************************************************************************************
* Libera a mem�ria utilizada por um endere�o e anula a refer�ncia
* @param endereco Refer�ncia para o endere�o
**************************************************************************************************/
void liberarEndereco(Endereco* endereco);

/**************************************************************************************************
* Libera a mem�ria utilizada por elementos de uma lista de endere�os
* @param elemento Elemento a ser liberado
* @param posicao Posi��o de ocorr�ncia na lista
**************************************************************************************************/
void liberarListaEnderecos(void* elemento, int posicao);

/**************************************************************************************************
* Cria uma nova empresa e inicializa seus atributos
* @param cnpj CNPJ da empresa no formato XX.XXX.XXX/XXXX-XX
* @param razaoSocial Raz�o social da empresa
* @param nomeFantasia Nome fantasia da empresa
* @param dataAbertura Data de abertura da empresa no formato DD/MM/AAAA
* @param endereco Endere�o da empresa
* @param contato Contato da empresa
* @return Refer�ncia para a empresa criada
**************************************************************************************************/
Empresa* criarEmpresa(const char* cnpj, const char* razaoSocial, const char* nomeFantasia, const char* dataAbertura, Endereco* endereco, Contato* contato);

/**************************************************************************************************
* Libera a mem�ria utilizada por uma empresa e anula a refer�ncia
* @param empresa Refer�ncia para a empresa
**************************************************************************************************/
void liberarEmpresa(Empresa* empresa);

/**************************************************************************************************
* Libera a mem�ria utilizada por elementos de uma lista de empresas
* @param elemento Elemento a ser liberado
* @param posicao Posi��o de ocorr�ncia na lista
**************************************************************************************************/
void liberarListaEmpresas(void* elemento, int posicao);

/**************************************************************************************************
* Cria um novo cliente e inicializa seus atributos
* @param nome Nome do cliente
* @param cargo Cargo do cliente
* @param contato Contato do cliente
* @param empresa Empresa do cliente
* @return Refer�ncia para o cliente criado
**************************************************************************************************/
Cliente* criarCliente(const char* nome, const char* cargo, Contato* contato, Empresa* empresa);

/**************************************************************************************************
* Libera a mem�ria utilizada por um cliente e anula a refer�ncia
* @param cliente Refer�ncia para o cliente
**************************************************************************************************/
void liberarCliente(Cliente* cliente);

/**************************************************************************************************
* Libera a mem�ria utilizada por elementos de uma lista de clientes
* @param elemento Elemento a ser liberado
* @param posicao Posi��o de ocorr�ncia na lista
**************************************************************************************************/
void liberarListaClientes(void* elemento, int posicao);

/**************************************************************************************************
* Converte uma string para um valor de regi�o
* @param regiao String de regi�o
* @return Valor de regi�o ou -1 se inv�lido
**************************************************************************************************/
int converterRegiaoDeString(const char* regiao);

/**************************************************************************************************
* Converte um valor de regi�o para uma string
* @param regiao Valor de regi�o
* @return String de regi�o ou NULL se inv�lido
**************************************************************************************************/
const char* converterStringDeRegiao(Regiao regiao);
