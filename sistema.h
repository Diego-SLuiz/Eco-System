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
* Cria um novo relatório e inicializa seus atributos
* @param residuosTratados Quantidade de resíduos tratados em KG
* @param valorEstimado Valor estimado em R$
* @param data Data de emissão do relatório no formato MM/AAAA
* @return Referência para o relatório criado
**************************************************************************************************/
Relatorio* criarRelatorio(int residuosTratados, float valorEstimado, const char* data);

/**************************************************************************************************
* Adiciona um relatório à lista de relatórios de um cliente
* @param cliente Cliente a ser associado ao relatório
* @param relatorio Relatório a ser adicionado
**************************************************************************************************/
void adicionarRelatorio(Cliente* cliente, Relatorio* relatorio);

/**************************************************************************************************
* Remove um relatório da lista de relatórios de um cliente
* @param cliente Cliente a ser desassociado do relatório
* @param posicao Posição de ocorrência na lista de relatórios
**************************************************************************************************/
void removerRelatorio(Cliente* cliente, int posicao);

/**************************************************************************************************
* Libera a memória utilizada por um relatório e anula a referência
* @param relatorio Referência para o relatório
**************************************************************************************************/
void liberarRelatorio(Relatorio* relatorio);

/**************************************************************************************************
* Libera a memória utilizada por elementos de uma lista de relatórios
* @param elemento Elemento a ser liberado
* @param posicao Posição de ocorrência na lista
**************************************************************************************************/
void liberarListaRelatorios(void* elemento, int posicao);

/**************************************************************************************************
* Cria um novo funcionário e inicializa seus atributos
* @param usuario Nome de usuário do funcionário
* @param senha Senha de acesso do funcionário
* @return Referência para o funcionário criado
**************************************************************************************************/
Funcionario* criarFuncionario(const char* usuario, const char* senha);

/**************************************************************************************************
* Libera a memória utilizada por um funcionário e anula a referência
* @param funcionario Referência para o funcionário
**************************************************************************************************/
void liberarFuncionario(Funcionario* funcionario);

/**************************************************************************************************
* Libera a memória utilizada por elementos de uma lista de funcionários
* @param elemento Elemento a ser liberado
* @param posicao Posição de ocorrência na lista
**************************************************************************************************/
void liberarListaFuncionarios(void* elemento, int posicao);

/**************************************************************************************************
* Cria um novo contato e inicializa seus atributos
* @param telefone Número de telefone do contato no formato (XX) XXXXX-XXXX
* @param email Endereço de e-mail do contato
* @return Referência para o contato criado
**************************************************************************************************/
Contato* criarContato(const char* telefone, const char* email);

/**************************************************************************************************
* Libera a memória utilizada por um contato e anula a referência
* @param contato Referência para o contato
**************************************************************************************************/
void liberarContato(Contato* contato);

/**************************************************************************************************
* Libera a memória utilizada por elementos de uma lista de contatos
* @param elemento Elemento a ser liberado
* @param posicao Posição de ocorrência na lista
**************************************************************************************************/
void liberarListaContatos(void* elemento, int posicao);

/**************************************************************************************************
* Cria um novo endereço e inicializa seus atributos
* @param cep CEP do endereço no formato XXXXX-XXX
* @param estado Sigla do estado do endereço no formato XX
* @param cidade Nome da cidade do endereço
* @param bairro Nome do bairro do endereço
* @param rua Nome da rua do endereço
* @param numero Número do endereço
* @param regiao Região do endereço
* @return Referência para o endereço criado
**************************************************************************************************/
Endereco* criarEndereco(const char* cep, const char* estado, const char* cidade, const char* bairro, const char* rua, const char* numero, Regiao regiao);

/**************************************************************************************************
* Libera a memória utilizada por um endereço e anula a referência
* @param endereco Referência para o endereço
**************************************************************************************************/
void liberarEndereco(Endereco* endereco);

/**************************************************************************************************
* Libera a memória utilizada por elementos de uma lista de endereços
* @param elemento Elemento a ser liberado
* @param posicao Posição de ocorrência na lista
**************************************************************************************************/
void liberarListaEnderecos(void* elemento, int posicao);

/**************************************************************************************************
* Cria uma nova empresa e inicializa seus atributos
* @param cnpj CNPJ da empresa no formato XX.XXX.XXX/XXXX-XX
* @param razaoSocial Razão social da empresa
* @param nomeFantasia Nome fantasia da empresa
* @param dataAbertura Data de abertura da empresa no formato DD/MM/AAAA
* @param endereco Endereço da empresa
* @param contato Contato da empresa
* @return Referência para a empresa criada
**************************************************************************************************/
Empresa* criarEmpresa(const char* cnpj, const char* razaoSocial, const char* nomeFantasia, const char* dataAbertura, Endereco* endereco, Contato* contato);

/**************************************************************************************************
* Libera a memória utilizada por uma empresa e anula a referência
* @param empresa Referência para a empresa
**************************************************************************************************/
void liberarEmpresa(Empresa* empresa);

/**************************************************************************************************
* Libera a memória utilizada por elementos de uma lista de empresas
* @param elemento Elemento a ser liberado
* @param posicao Posição de ocorrência na lista
**************************************************************************************************/
void liberarListaEmpresas(void* elemento, int posicao);

/**************************************************************************************************
* Cria um novo cliente e inicializa seus atributos
* @param nome Nome do cliente
* @param cargo Cargo do cliente
* @param contato Contato do cliente
* @param empresa Empresa do cliente
* @return Referência para o cliente criado
**************************************************************************************************/
Cliente* criarCliente(const char* nome, const char* cargo, Contato* contato, Empresa* empresa);

/**************************************************************************************************
* Libera a memória utilizada por um cliente e anula a referência
* @param cliente Referência para o cliente
**************************************************************************************************/
void liberarCliente(Cliente* cliente);

/**************************************************************************************************
* Libera a memória utilizada por elementos de uma lista de clientes
* @param elemento Elemento a ser liberado
* @param posicao Posição de ocorrência na lista
**************************************************************************************************/
void liberarListaClientes(void* elemento, int posicao);

/**************************************************************************************************
* Converte uma string para um valor de região
* @param regiao String de região
* @return Valor de região ou -1 se inválido
**************************************************************************************************/
int converterRegiaoDeString(const char* regiao);

/**************************************************************************************************
* Converte um valor de região para uma string
* @param regiao Valor de região
* @return String de região ou NULL se inválido
**************************************************************************************************/
const char* converterStringDeRegiao(Regiao regiao);
