#include <stdio.h>
#include <string.h>

#include "arquivo.h"
#include "lista.h"
#include "memoria.h"

#define tamanhoInteiro 9
#define tamanhoDecimal 12
#define TAMANHO_LINHA 8192

char* ARQUIVO_FUNCIONARIOS = "funcionarios.dat";
char* ARQUIVO_CLIENTES = "clientes.dat";
char* ARQUIVO_RELATORIO_CLIENTES = "Clientes.csv";
char* ARQUIVO_RELATORIO_FATURAMENTO = "Faturamento.csv";

/**************************************************************************************************
* Abre um arquivo no modo especificado e verifica se a operação foi bem-sucedida
* @param caminho Caminho do arquivo
* @param modo Modo de abertura do arquivo
* @return Referência para o arquivo aberto
**************************************************************************************************/
static FILE* abrirArquivo(const char* caminho, const char* modo) {
	if (caminho == NULL || modo == NULL) {
		fprintf(stderr, "Erro ao abrir arquivo: parametros nulos\n");
		exit(2);
	}

	FILE* arquivo = fopen(caminho, modo);

	if (arquivo == NULL) {
		perror("Erro ao abrir arquivo");
		exit(4);
	}

	return arquivo;
}

/**************************************************************************************************
* Fecha um arquivo e anula a referência
* @param arquivo Ponteiro para a referência do arquivo
**************************************************************************************************/
static void fecharArquivo(FILE** arquivo) {
	if (arquivo != NULL && *arquivo != NULL) {
		fclose(*arquivo);
		*arquivo = NULL;
	}
}

/**************************************************************************************************
* Concatena os elementos de uma lista em uma string separada por um caractere
* @param elementos Lista de elementos
* @param separador Caractere separador
* @return String resultante
**************************************************************************************************/
static char* concatenar(Lista* elementos, char separador) {
	if (elementos == NULL || separador == NULL) {
		fprintf(stderr, "Erro ao concatenar elementos: parametros nulos\n");
		exit(2);
	}

	if (elementos->tamanho == 0) {
		fprintf(stderr, "Erro ao concatenar elementos: lista vazia\n");
		exit(3);
	}

	char* resultado = NULL;

	for (int i = 0; i < elementos->tamanho; i++) {
		char* elemento = obterElemento(elementos, i);
		int ultimoElemento = i + 1 == elementos->tamanho;

		if (elemento == NULL) {
			fprintf(stderr, "Erro ao concatenar elementos: elemento %d nulo\n", i);
			exit(2);
		}

		size_t tamanhoElemento = strlen(elemento);
		size_t tamanhoSeparador = 1;
		char* ocorrenciaAtual = alocarMemoria(tamanhoElemento + tamanhoSeparador + 1);

		strncpy_s(ocorrenciaAtual, tamanhoElemento + tamanhoSeparador + 1, elemento, tamanhoElemento);
		
		if (!ultimoElemento) {
			ocorrenciaAtual[tamanhoElemento] = separador;
			ocorrenciaAtual[tamanhoElemento + tamanhoSeparador] = '\0';
		}
		
		if (resultado == NULL) {
			resultado = ocorrenciaAtual;
			continue;
		}
		
		size_t tamanhoResultado = strlen(resultado);
		size_t tamanhoOcorrenciaAtual = strlen(ocorrenciaAtual);
			
		resultado = realocarMemoria(resultado, tamanhoResultado + tamanhoOcorrenciaAtual + 1);
		strncpy_s(resultado + tamanhoResultado, tamanhoOcorrenciaAtual + 1, ocorrenciaAtual, tamanhoOcorrenciaAtual);
		liberarMemoria(&ocorrenciaAtual);
	}

	return resultado;
}

/**************************************************************************************************
* Divide uma string em uma lista de strings a partir de um caractere separador
* @param texto String a ser dividida
* @param separador Caractere separador
* @return Lista de strings resultante
**************************************************************************************************/
static Lista* dividir(const char* texto, char separador) {
	if (texto == NULL || separador == NULL) {
		fprintf(stderr, "Erro ao dividir string: parametros nulos\n");
		exit(2);
	}

	int tamanhoTexto = strlen(texto);
	int tamanhoSeparador = 1;
	int deslocamento = 0;
	Lista* resultado = criarLista();

	for (int i = 0; i <= tamanhoTexto; i++) {
		int separadorEncontrado = texto[i] == separador;
		int ultimoElemento = texto[i] == '\0';

		if (separadorEncontrado || ultimoElemento) {
			size_t tamanhoOcorrenciaAtual = i - deslocamento;
			char* ocorrenciaAtual = alocarMemoria(tamanhoOcorrenciaAtual + 1);

			strncpy_s(ocorrenciaAtual, tamanhoOcorrenciaAtual + 1, texto + deslocamento, tamanhoOcorrenciaAtual);
			adicionarElemento(resultado, ocorrenciaAtual);
			deslocamento += tamanhoOcorrenciaAtual + tamanhoSeparador;
		}
	}

	return resultado;
}

/**************************************************************************************************
* Converte um inteiro para uma string
* @param entrada Inteiro a ser convertido
* @param destino Vetor para armazenar a string resultante
**************************************************************************************************/
static void converterDeInteiro(int entrada, char* destino) {
	if (destino == NULL) {
		fprintf(stderr, "Erro ao converter de inteiro: parametros nulos\n");
		exit(2);
	}

	sprintf_s(destino, tamanhoInteiro, "%d", entrada);
}

/**************************************************************************************************
* Converte uma string para um inteiro
* @param entrada String a ser convertida
* @return Inteiro resultante
**************************************************************************************************/
static int converterParaInteiro(const char* entrada) {
	if (entrada == NULL) {
		fprintf(stderr, "Erro ao converter para inteiro: parametros nulos\n");
		exit(2);
	}

	return atoi(entrada);
}

/**************************************************************************************************
* Converte um decimal para uma string
* @param entrada Decimal a ser convertido
* @param destino Vetor para armazenar a string resultante
**************************************************************************************************/
static void converterDeDecimal(float entrada, char* destino) {
	if (destino == NULL) {
		fprintf(stderr, "Erro ao converter de decimal: parametros nulos\n");
		exit(2);
	}

	sprintf_s(destino, tamanhoDecimal, "%.2f", entrada);
}

/**************************************************************************************************
* Converte uma string para um decimal
* @param entrada String a ser convertida
* @return Decimal resultante
**************************************************************************************************/
static float converterParaDecimal(const char* entrada) {
	if (entrada == NULL) {
		fprintf(stderr, "Erro ao converter para decimal: parametros nulos\n");
		exit(2);
	}

	return atof(entrada);
}

/**************************************************************************************************
* Carrega um funcionário a partir de uma string
* @param dadosFuncionario String com os dados do funcionário separados por vírgula
* @return Funcionário resultante
**************************************************************************************************/
static Funcionario* carregarFuncionario(char* dadosFuncionario) {
	if (dadosFuncionario == NULL) {
		fprintf(stderr, "Erro ao carregar funcionario: parametros nulos\n");
		exit(2);
	}

	dadosFuncionario[strlen(dadosFuncionario) - 1] = '\0';

	Lista* atributos = dividir(dadosFuncionario, ',');
	char* usuario = obterElemento(atributos, 0);
	char* senha = obterElemento(atributos, 1);

	Funcionario* funcionario = criarFuncionario(usuario, senha);
	
	percorrerLista(atributos, liberarListaElementos);
	liberarLista(atributos);

	return funcionario;

}

/**************************************************************************************************
* Carrega um cliente a partir de uma string
* @param dadosCliente String com os dados do cliente separados por vírgula
* @return Cliente resultante
**************************************************************************************************/
static Cliente* carregarCliente(char* dadosCliente) {
	if (dadosCliente == NULL) {
		fprintf(stderr, "Erro ao carregar cliente: parametros nulos\n");
		exit(2);
	}

	dadosCliente[strlen(dadosCliente) - 1] = '\0';
	Lista* atributos = dividir(dadosCliente, ',');

	char* nome = obterElemento(atributos, 0);
	char* cargo = obterElemento(atributos, 1);

	char* emailCliente = obterElemento(atributos, 2);
	char* telefoneCliente = obterElemento(atributos, 3);

	char* cnpj = obterElemento(atributos, 4);
	char* razaoSocial = obterElemento(atributos, 5);
	char* nomeFantasia = obterElemento(atributos, 6);
	char* dataAbertura = obterElemento(atributos, 7);

	char* emailEmpresa = obterElemento(atributos, 8);
	char* telefoneEmpresa = obterElemento(atributos, 9);

	char* cep = obterElemento(atributos, 10);
	char* estado = obterElemento(atributos, 11);
	char* cidade = obterElemento(atributos, 12);
	char* bairro = obterElemento(atributos, 13);
	char* rua = obterElemento(atributos, 14);
	char* numero = obterElemento(atributos, 15);
	Regiao regiao = converterParaInteiro(obterElemento(atributos, 16));

	Lista* relatorios = criarLista();
	int quantidadeRelatorios = converterParaInteiro(obterElemento(atributos, 17));

	for (int i = 0; i < quantidadeRelatorios; i++) {
		int residuosTratados = converterParaInteiro(obterElemento(atributos, 18 + i * 3));
		float valorEstimado = converterParaDecimal(obterElemento(atributos, 19 + i * 3));
		char* data = obterElemento(atributos, 20 + i * 3);

		Relatorio* relatorio = criarRelatorio(residuosTratados, valorEstimado, data);
		adicionarElemento(relatorios, relatorio);
	}

	Contato* contatoEmpresa = criarContato(telefoneEmpresa, emailEmpresa);
	Endereco* enderecoEmpresa = criarEndereco(cep, estado, cidade, bairro, rua, numero, regiao);
	Empresa* empresaCliente = criarEmpresa(cnpj, razaoSocial, nomeFantasia, dataAbertura, enderecoEmpresa, contatoEmpresa);

	Contato* contatoCliente = criarContato(telefoneCliente, emailCliente);
	Cliente* cliente = criarCliente(nome, cargo, contatoCliente, empresaCliente);

	liberarLista(cliente->relatorios);
	cliente->relatorios = relatorios;

	percorrerLista(atributos, liberarListaElementos);
	liberarLista(atributos);
	
	return cliente;
}

void salvarFuncionario(Funcionario* funcionario) {
	if (funcionario == NULL) {
		fprintf(stderr, "Erro ao salvar funcionario: parametros nulos\n");
		exit(2);
	}

	FILE* arquivo = abrirArquivo(ARQUIVO_FUNCIONARIOS, "a");
	Lista* dadosFuncionario = criarLista();

	char* nome = funcionario->usuario;
	char* cargo = funcionario->senha;

	adicionarElemento(dadosFuncionario, nome);
	adicionarElemento(dadosFuncionario, cargo);

	char* resultado = concatenar(dadosFuncionario, ',');
	fprintf(arquivo, "%s\n", resultado);

	fecharArquivo(&arquivo);
	liberarMemoria(&resultado);
	liberarLista(dadosFuncionario);
}

void removerFuncionario(Funcionario* funcionario) {
	if (funcionario == NULL) {
		fprintf(stderr, "Erro ao remover funcionario: parametros nulos\n");
		exit(2);
	}

	char entrada[TAMANHO_LINHA];
	FILE* arquivo = abrirArquivo(ARQUIVO_FUNCIONARIOS, "r");
	FILE* arquivoTemporario = abrirArquivo("tmp.txt", "w");

	while (fgets(entrada, TAMANHO_LINHA, arquivo) != NULL) {
		Funcionario* funcionarioAtual = carregarFuncionario(entrada);

		if (strcmp(funcionarioAtual->usuario, funcionario->usuario) != 0) {
			fprintf(arquivoTemporario, "%s\n", entrada);
		}

		liberarFuncionario(funcionarioAtual);
	}

	fclose(arquivo);
	fclose(arquivoTemporario);

	int removeu = remove(ARQUIVO_FUNCIONARIOS);
	int renomeou = rename("tmp.txt", ARQUIVO_FUNCIONARIOS);

	if (removeu != 0) {
		perror("Erro ao remover arquivo");
		exit(4);
	}

	if (renomeou != 0) {
		perror("Erro ao renomear arquivo");
		exit(4);
	}

	fecharArquivo(&arquivo);
	fecharArquivo(&arquivoTemporario);
}

Lista* carregarListaFuncionarios() {
	FILE* arquivo = abrirArquivo(ARQUIVO_FUNCIONARIOS, "r");
	Lista* resultado = criarLista();
	char entrada[TAMANHO_LINHA];

	while (fgets(entrada, TAMANHO_LINHA, arquivo) != NULL) {
		Funcionario* funcionario = carregarFuncionario(entrada);
		adicionarElemento(resultado, funcionario);
	}

	fecharArquivo(&arquivo);
	return resultado;
}

Funcionario* carregarFuncionarioPorUsuario(const char* usuario) {
	if (usuario == NULL) {
		fprintf(stderr, "Erro ao carregar funcionario por usuario: parametros nulos\n");
		exit(2);
	}

	FILE* arquivo = abrirArquivo(ARQUIVO_FUNCIONARIOS, "r");
	char entrada[TAMANHO_LINHA];

	while (fgets(entrada, TAMANHO_LINHA, arquivo) != NULL) {
		Funcionario* funcionario = carregarFuncionario(entrada);
		
		if (strcmp(funcionario->usuario, usuario) == 0) {
			fecharArquivo(&arquivo);
			return funcionario;
		}
		else {
			liberarFuncionario(funcionario);
		}
	}

	fecharArquivo(&arquivo);
	return NULL;
}

void salvarCliente(Cliente* cliente) {
	if (cliente == NULL) {
		fprintf(stderr, "Erro ao salvar cliente: parametros nulos\n");
		exit(2);
	}

	Contato* contatoCliente = cliente->contato;
	Empresa* empresaCliente = cliente->empresa;
	Lista* relatorios = cliente->relatorios;

	Contato* contatoEmpresa = empresaCliente->contato;
	Endereco* enderecoEmpresa = empresaCliente->endereco;

	if (contatoCliente == NULL || empresaCliente == NULL || relatorios == NULL || contatoEmpresa == NULL || enderecoEmpresa == NULL) {
		fprintf(stderr, "Erro ao salvar cliente: parametros nulos\n");
		exit(2);
	}

	FILE* arquivo = abrirArquivo(ARQUIVO_CLIENTES, "a");
	Lista* dadosCliente = criarLista();

	char* nome = duplicarString(cliente->nome);
	char* cargo = duplicarString(cliente->cargo);
	adicionarElemento(dadosCliente, nome);
	adicionarElemento(dadosCliente, cargo);

	char* emailCliente = duplicarString(cliente->contato->email);
	char* telefoneCliente = duplicarString(cliente->contato->telefone);
	adicionarElemento(dadosCliente, emailCliente);
	adicionarElemento(dadosCliente, telefoneCliente);

	char* cnpj = duplicarString(empresaCliente->cnpj);
	char* razaoSocial = duplicarString(empresaCliente->razaoSocial);
	char* nomeFantasia = duplicarString(empresaCliente->nomeFantasia);
	char* dataAbertura = duplicarString(empresaCliente->dataAbertura);
	adicionarElemento(dadosCliente, cnpj);
	adicionarElemento(dadosCliente, razaoSocial);
	adicionarElemento(dadosCliente, nomeFantasia);
	adicionarElemento(dadosCliente, dataAbertura);

	char* emailEmpresa = duplicarString(empresaCliente->contato->email);
	char* telefoneEmpresa = duplicarString(empresaCliente->contato->telefone);
	adicionarElemento(dadosCliente, emailEmpresa);
	adicionarElemento(dadosCliente, telefoneEmpresa);

	char* cep = duplicarString(empresaCliente->endereco->cep);
	char* estado = duplicarString(empresaCliente->endereco->estado);
	char* cidade = duplicarString(empresaCliente->endereco->cidade);
	char* bairro = duplicarString(empresaCliente->endereco->bairro);
	char* rua = duplicarString(empresaCliente->endereco->rua);
	char* numero = duplicarString(empresaCliente->endereco->numero);
	char regiao[tamanhoInteiro];
	converterDeInteiro(empresaCliente->endereco->regiao, regiao);
	adicionarElemento(dadosCliente, cep);
	adicionarElemento(dadosCliente, estado);
	adicionarElemento(dadosCliente, cidade);
	adicionarElemento(dadosCliente, bairro);
	adicionarElemento(dadosCliente, rua);
	adicionarElemento(dadosCliente, numero);
	adicionarElemento(dadosCliente, duplicarString(regiao));

	char quantidadeRelatorios[tamanhoInteiro];
	converterDeInteiro(relatorios->tamanho, quantidadeRelatorios);
	adicionarElemento(dadosCliente, duplicarString(quantidadeRelatorios));

	for (int i = 0; i < relatorios->tamanho; i++) {
		Relatorio* relatorio = obterElemento(relatorios, i);

		if (relatorio == NULL) {
			fprintf(stderr, "Erro ao salvar cliente: relatorio %d nulo\n", i);
			exit(2);
		}

		char residuosTratados[tamanhoInteiro];
		char valorEstimado[tamanhoDecimal];
		char* data = duplicarString(relatorio->data);

		converterDeInteiro(relatorio->residuosTratados, residuosTratados);
		adicionarElemento(dadosCliente, duplicarString(residuosTratados));

		converterDeDecimal(relatorio->valorEstimado, valorEstimado);
		adicionarElemento(dadosCliente, duplicarString(valorEstimado));

		adicionarElemento(dadosCliente, data);
	}

	char* resultado = concatenar(dadosCliente, ',');
	fprintf(arquivo, "%s\n", resultado);

	fecharArquivo(&arquivo);
	liberarMemoria(&resultado);
	percorrerLista(dadosCliente, liberarListaElementos);
	liberarLista(dadosCliente);
}

void atualizarCliente(Cliente* cliente) {
	if (cliente == NULL) {
		fprintf(stderr, "Erro ao atualizar cliente: parametros nulos\n");
		exit(2);
	}

	char entrada[TAMANHO_LINHA];
	FILE* arquivo = abrirArquivo(ARQUIVO_CLIENTES, "r");
	FILE* arquivoTemporario = abrirArquivo("tmp.txt", "w");

	while (fgets(entrada, TAMANHO_LINHA, arquivo) != NULL) {
		Cliente* clienteAtual = carregarCliente(entrada);

		if (strcmp(cliente->empresa->cnpj, cliente->empresa->cnpj) == 0) {
			Contato* contatoCliente = cliente->contato;
			Empresa* empresaCliente = cliente->empresa;
			Lista* relatorios = cliente->relatorios;

			Contato* contatoEmpresa = empresaCliente->contato;
			Endereco* enderecoEmpresa = empresaCliente->endereco;

			if (contatoCliente == NULL || empresaCliente == NULL || relatorios == NULL || contatoEmpresa == NULL || enderecoEmpresa == NULL) {
				fprintf(stderr, "Erro ao salvar cliente: parametros nulos\n");
				exit(2);
			}

			Lista* dadosCliente = criarLista();

			char* nome = duplicarString(cliente->nome);
			char* cargo = duplicarString(cliente->cargo);
			adicionarElemento(dadosCliente, nome);
			adicionarElemento(dadosCliente, cargo);

			char* emailCliente = duplicarString(cliente->contato->email);
			char* telefoneCliente = duplicarString(cliente->contato->telefone);
			adicionarElemento(dadosCliente, emailCliente);
			adicionarElemento(dadosCliente, telefoneCliente);

			char* cnpj = duplicarString(empresaCliente->cnpj);
			char* razaoSocial = duplicarString(empresaCliente->razaoSocial);
			char* nomeFantasia = duplicarString(empresaCliente->nomeFantasia);
			char* dataAbertura = duplicarString(empresaCliente->dataAbertura);
			adicionarElemento(dadosCliente, cnpj);
			adicionarElemento(dadosCliente, razaoSocial);
			adicionarElemento(dadosCliente, nomeFantasia);
			adicionarElemento(dadosCliente, dataAbertura);

			char* emailEmpresa = duplicarString(empresaCliente->contato->email);
			char* telefoneEmpresa = duplicarString(empresaCliente->contato->telefone);
			adicionarElemento(dadosCliente, emailEmpresa);
			adicionarElemento(dadosCliente, telefoneEmpresa);

			char* cep = duplicarString(empresaCliente->endereco->cep);
			char* estado = duplicarString(empresaCliente->endereco->estado);
			char* cidade = duplicarString(empresaCliente->endereco->cidade);
			char* bairro = duplicarString(empresaCliente->endereco->bairro);
			char* rua = duplicarString(empresaCliente->endereco->rua);
			char* numero = duplicarString(empresaCliente->endereco->numero);
			char regiao[tamanhoInteiro];
			converterDeInteiro(empresaCliente->endereco->regiao, regiao);
			adicionarElemento(dadosCliente, cep);
			adicionarElemento(dadosCliente, estado);
			adicionarElemento(dadosCliente, cidade);
			adicionarElemento(dadosCliente, bairro);
			adicionarElemento(dadosCliente, rua);
			adicionarElemento(dadosCliente, numero);
			adicionarElemento(dadosCliente, duplicarString(regiao));

			char quantidadeRelatorios[tamanhoInteiro];
			converterDeInteiro(relatorios->tamanho, quantidadeRelatorios);
			adicionarElemento(dadosCliente, duplicarString(quantidadeRelatorios));

			for (int i = 0; i < relatorios->tamanho; i++) {
				Relatorio* relatorio = obterElemento(relatorios, i);

				if (relatorio == NULL) {
					fprintf(stderr, "Erro ao salvar cliente: relatorio %d nulo\n", i);
					exit(2);
				}

				char residuosTratados[tamanhoInteiro];
				char valorEstimado[tamanhoDecimal];
				char* data = duplicarString(relatorio->data);

				converterDeInteiro(relatorio->residuosTratados, residuosTratados);
				adicionarElemento(dadosCliente, duplicarString(residuosTratados));

				converterDeDecimal(relatorio->valorEstimado, valorEstimado);
				adicionarElemento(dadosCliente, duplicarString(valorEstimado));

				adicionarElemento(dadosCliente, data);
			}

			char* resultado = concatenar(dadosCliente, ',');
			fprintf(arquivoTemporario, "%s\n", resultado);

			liberarMemoria(&resultado);
			percorrerLista(dadosCliente, liberarListaElementos);
			liberarLista(dadosCliente);
		}
		else {
			fprintf(arquivoTemporario, "%s\n", entrada);
		}

		liberarCliente(clienteAtual);
	}

	fclose(arquivo);
	fclose(arquivoTemporario);

	int removou = remove(ARQUIVO_CLIENTES);
	int renomeou = rename("tmp.txt", ARQUIVO_CLIENTES);

	if (removou != 0) {
		perror("Erro ao remover arquivo");
		exit(4);
	}

	if (renomeou != 0) {
		perror("Erro ao renomear arquivo");
		exit(4);
	}

	fecharArquivo(&arquivo);
	fecharArquivo(&arquivoTemporario);
}

void removerCliente(Cliente* cliente) {
	if (cliente == NULL) {
		fprintf(stderr, "Erro ao remover cliente: parametros nulos\n");
		exit(2);
	}
	
	char entrada[TAMANHO_LINHA];
	FILE* arquivo = abrirArquivo(ARQUIVO_CLIENTES, "r");
	FILE* arquivoTemporario = abrirArquivo("tmp.txt", "w");

	while (fgets(entrada, TAMANHO_LINHA, arquivo) != NULL) {
		Cliente* clienteAtual = carregarCliente(entrada);

		if (strcmp(clienteAtual->empresa->cnpj, cliente->empresa->cnpj) != 0) {
			fprintf(arquivoTemporario, "%s\n", entrada);
		}

		liberarCliente(clienteAtual);
	}

	fclose(arquivo);
	fclose(arquivoTemporario);

	int removou = remove(ARQUIVO_CLIENTES);
	int renomeou = rename("tmp.txt", ARQUIVO_CLIENTES);

	if (removou != 0) {
		perror("Erro ao remover arquivo");
		exit(4);
	}

	if (renomeou != 0) {
		perror("Erro ao renomear arquivo");
		exit(4);
	}

	fecharArquivo(&arquivo);
	fecharArquivo(&arquivoTemporario);
}

Lista* carregarListaClientes() {
	FILE* arquivo = abrirArquivo(ARQUIVO_CLIENTES, "r");
	Lista* resultado = criarLista();
	char entrada[TAMANHO_LINHA];

	while (fgets(entrada, TAMANHO_LINHA, arquivo) != NULL) {
		Cliente* cliente = carregarCliente(entrada);	
		adicionarElemento(resultado, cliente);
	}

	fecharArquivo(&arquivo);
	return resultado;
}

Cliente* carregarClientePorCNPJ(const char* cnpj) {
	if (cnpj == NULL) {
		fprintf(stderr, "Erro ao carregar cliente por cnpj: parametros nulos\n");
		exit(2);
	}

	FILE* arquivo = abrirArquivo(ARQUIVO_CLIENTES, "r");
	char entrada[TAMANHO_LINHA];

	while (fgets(entrada, TAMANHO_LINHA, arquivo) != NULL) {
		Cliente* cliente = carregarCliente(entrada);

		if (strcmp(cliente->empresa->cnpj, cnpj) == 0) {
			fecharArquivo(&arquivo);
			return cliente;
		}
		else {
			liberarCliente(cliente);
		}
	}

	fecharArquivo(&arquivo);
	return NULL;
}

void gerarRelatorioClientes() {
	FILE* arquivo = abrirArquivo(ARQUIVO_RELATORIO_CLIENTES, "w");

	const char* cabecalho = "Nome do Cliente,Cargo do Cliente,Telefone do Cliente,E-mail do Cliente,CNPJ da Empresa,Razao Social da Empresa,Nome Fantasia da Empresa,Data de Abertura da Empresa,CEP,Sigla do Estado,Cidade,Bairro,Logradouro,Número,Região,Telefone da Empresa,E-mail da Empresa";
	fprintf(arquivo, "%s\n", cabecalho);

	Lista* clientes = carregarListaClientes();

	for (int i = 0; i < clientes->tamanho; i++) {
		Cliente* cliente = obterElemento(clientes, i);

		if (cliente == NULL) {
			fprintf(stderr, "Erro ao gerar relatorio de clientes: parametros nulos\n");
			exit(2);
		}

		Contato* contatoCliente = cliente->contato;

		Empresa* empresa = cliente->empresa;
		Contato* contatoEmpresa = empresa->contato;
		Endereco* enderecoEmpresa = empresa->endereco;

		Lista* dadosCliente = criarLista();
		adicionarElemento(dadosCliente, duplicarString(cliente->nome));
		adicionarElemento(dadosCliente, duplicarString(cliente->cargo));
		adicionarElemento(dadosCliente, duplicarString(contatoCliente->telefone));
		adicionarElemento(dadosCliente, duplicarString(contatoCliente->email));
		adicionarElemento(dadosCliente, duplicarString(empresa->cnpj));
		adicionarElemento(dadosCliente, duplicarString(empresa->razaoSocial));
		adicionarElemento(dadosCliente, duplicarString(empresa->nomeFantasia));
		adicionarElemento(dadosCliente, duplicarString(empresa->dataAbertura));
		adicionarElemento(dadosCliente, duplicarString(enderecoEmpresa->cep));
		adicionarElemento(dadosCliente, duplicarString(enderecoEmpresa->estado));
		adicionarElemento(dadosCliente, duplicarString(enderecoEmpresa->cidade));
		adicionarElemento(dadosCliente, duplicarString(enderecoEmpresa->bairro));
		adicionarElemento(dadosCliente, duplicarString(enderecoEmpresa->rua));
		adicionarElemento(dadosCliente, duplicarString(enderecoEmpresa->numero));
		adicionarElemento(dadosCliente, duplicarString(converterStringDeRegiao(enderecoEmpresa->regiao)));
		adicionarElemento(dadosCliente, duplicarString(contatoEmpresa->telefone));
		adicionarElemento(dadosCliente, duplicarString(contatoEmpresa->email));

		char* resultado = concatenar(dadosCliente, ',');
		fprintf(arquivo, "%s\n", resultado);

		liberarMemoria(&resultado);
		percorrerLista(dadosCliente, liberarListaElementos);
		liberarLista(dadosCliente);
	}

	percorrerLista(clientes, liberarListaClientes);
	liberarLista(clientes);
	fecharArquivo(&arquivo);
}

void gerarRelatorioFaturamento() {
	FILE* arquivo = abrirArquivo(ARQUIVO_RELATORIO_FATURAMENTO, "w");

	const char* cabecalho = "CNPJ,Razao Social,Contratante,Cargo,Residuos Tratados (KG),Valor Estimado (R$),Data,Regiao";
	fprintf(arquivo, "%s\n", cabecalho);

	Lista* clientes = carregarListaClientes();

	for (int i = 0; i < clientes->tamanho; i++) {\
		Cliente* cliente = obterElemento(clientes, i);

		if (cliente == NULL) {
			fprintf(stderr, "Erro ao gerar relatorio de faturamento: parametros nulos\n");
			exit(2);
		}

		Contato* contatoCliente = cliente->contato;

		Empresa* empresa = cliente->empresa;
		Contato* contatoEmpresa = empresa->contato;
		Endereco* enderecoEmpresa = empresa->endereco;

		Lista* relatorios = cliente->relatorios;

		for (int i = 0; i < relatorios->tamanho; i++) {
			Relatorio* relatorio = obterElemento(relatorios, i);

			if (relatorio == NULL) {
				fprintf(stderr, "Erro ao gerar relatorio de faturamento: parametros nulos\n");
				exit(2);
			}

			char* residuosTratados = alocarMemoria(tamanhoInteiro);
			char* valorEstimado = alocarMemoria(tamanhoDecimal);

			converterDeInteiro(relatorio->residuosTratados, residuosTratados);
			converterDeDecimal(relatorio->valorEstimado, valorEstimado);

			Lista* dadosRelatorio = criarLista();
			adicionarElemento(dadosRelatorio, duplicarString(empresa->cnpj));
			adicionarElemento(dadosRelatorio, duplicarString(empresa->razaoSocial));
			adicionarElemento(dadosRelatorio, duplicarString(cliente->nome));
			adicionarElemento(dadosRelatorio, duplicarString(cliente->cargo));
			adicionarElemento(dadosRelatorio, residuosTratados);
			adicionarElemento(dadosRelatorio, valorEstimado);
			adicionarElemento(dadosRelatorio, duplicarString(relatorio->data));
			adicionarElemento(dadosRelatorio, duplicarString(converterStringDeRegiao(enderecoEmpresa->regiao)));

			char* resultado = concatenar(dadosRelatorio, ',');
			fprintf(arquivo, "%s\n", resultado);

			liberarMemoria(&resultado);
			percorrerLista(dadosRelatorio, liberarListaElementos);
			liberarLista(dadosRelatorio);
		}
	}

	percorrerLista(clientes, liberarListaClientes);
	liberarLista(clientes);
	fecharArquivo(&arquivo);
}
