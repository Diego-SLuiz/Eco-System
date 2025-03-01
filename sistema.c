#include <stdio.h>
#include <string.h>

#include "memoria.h"
#include "sistema.h"

Relatorio* criarRelatorio(int residuosTratados, float valorEstimado, const char* data) {
	if (data == NULL) {
		fprintf(stderr, "Erro ao criar novo relatorio: parametros nulos\n");
		exit(2);
	}

	Relatorio* relatorio = alocarMemoria(sizeof(Relatorio));

	relatorio->residuosTratados = residuosTratados;
	relatorio->valorEstimado = valorEstimado;

	relatorio->data = duplicarString(data);

	return relatorio;
}

void adicionarRelatorio(Cliente* cliente, Relatorio* relatorio) {
	if (cliente == NULL || relatorio == NULL) {
		fprintf(stderr, "Erro ao adicionar relatorio: parametros nulos\n");
		exit(2);
	}

	adicionarElemento(cliente->relatorios, relatorio);
}

void removerRelatorio(Cliente* cliente, int posicao) {
	if (cliente == NULL) {
		fprintf(stderr, "Erro ao remover relatorio: parametros nulos\n");
		exit(2);
	}

	removerElemento(cliente->relatorios, posicao);
}

void liberarRelatorio(Relatorio* relatorio) {
	if (relatorio != NULL) {
		liberarMemoria(&relatorio->data);
		liberarMemoria(&relatorio);
	}
}

void liberarListaRelatorios(void* elemento, int posicao) {
	if (elemento != NULL) {
		Relatorio* relatorio = (Relatorio*) elemento;
		liberarRelatorio(relatorio);
	}
}

Funcionario* criarFuncionario(const char* usuario, const char* senha) {
	if (usuario == NULL || senha == NULL) {
		fprintf(stderr, "Erro ao criar novo funcionario: parametros nulos\n");
		exit(2);
	}

	Funcionario* funcionario = alocarMemoria(sizeof(Funcionario));

	funcionario->usuario = duplicarString(usuario);
	funcionario->senha = duplicarString(senha);

	return funcionario;
}

void liberarFuncionario(Funcionario* funcionario) {
	if (funcionario != NULL) {
		liberarMemoria(&funcionario->usuario);
		liberarMemoria(&funcionario->senha);
		liberarMemoria(&funcionario);
	}
}

void liberarListaFuncionarios(void* elemento, int posicao) {
	if (elemento != NULL) {
		Funcionario* funcionario = (Funcionario*) elemento;
		liberarFuncionario(funcionario);
	}
}

Contato* criarContato(const char* telefone, const char* email) {
	if (telefone == NULL || email == NULL) {
		fprintf(stderr, "Erro ao criar novo contato: parametros nulos\n");
		exit(2);
	}

	Contato* contato = alocarMemoria(sizeof(Contato));

	contato->telefone = duplicarString(telefone);
	contato->email = duplicarString(email);

	return contato;
}

void liberarContato(Contato* contato) {
	if (contato != NULL) {
		liberarMemoria(&contato->telefone);
		liberarMemoria(&contato->email);
		liberarMemoria(&contato);
	}
}

void liberarListaContatos(void* elemento, int posicao) {
	if (elemento != NULL) {
		Contato* contato = (Contato*) elemento;
		liberarContato(contato);
	}
}

Endereco* criarEndereco(const char* cep, const char* estado, const char* cidade, const char* bairro, const char* rua, const char* numero, Regiao regiao) {
	if (cep == NULL || estado == NULL || cidade == NULL || bairro == NULL || rua == NULL || numero == NULL) {
		fprintf(stderr, "Erro ao criar novo endereco: parametros nulos\n");
		exit(2);
	}

	Endereco* endereco = alocarMemoria(sizeof(Endereco));

	endereco->cep = duplicarString(cep);
	endereco->estado = duplicarString(estado);
	endereco->cidade = duplicarString(cidade);
	endereco->bairro = duplicarString(bairro);
	endereco->rua = duplicarString(rua);
	endereco->numero = duplicarString(numero);

	endereco->regiao = regiao;

	return endereco;
}

void liberarEndereco(Endereco* endereco) {
	if (endereco != NULL) {
		liberarMemoria(&endereco->cep);
		liberarMemoria(&endereco->estado);
		liberarMemoria(&endereco->cidade);
		liberarMemoria(&endereco->bairro);
		liberarMemoria(&endereco->rua);
		liberarMemoria(&endereco->numero);
		liberarMemoria(&endereco);
	}
}

void liberarListaEnderecos(void* elemento, int posicao) {
	if (elemento != NULL) {
		Endereco* endereco = (Endereco*) elemento;
		liberarEndereco(endereco);
	}
}

Empresa* criarEmpresa(const char* cnpj, const char* razaoSocial, const char* nomeFantasia, const char* dataAbertura, Endereco* endereco, Contato* contato) {
	if (cnpj == NULL || razaoSocial == NULL || nomeFantasia == NULL || dataAbertura == NULL || endereco == NULL || contato == NULL) {
		fprintf(stderr, "Erro ao criar nova empresa: parametros nulos\n");
		exit(2);
	}

	Empresa* empresa = alocarMemoria(sizeof(Empresa));

	empresa->cnpj = duplicarString(cnpj);
	empresa->razaoSocial = duplicarString(razaoSocial);
	empresa->nomeFantasia = duplicarString(nomeFantasia);
	empresa->dataAbertura = duplicarString(dataAbertura);

	empresa->endereco = endereco;
	empresa->contato = contato;

	return empresa;
}

void liberarEmpresa(Empresa* empresa) {
	if (empresa != NULL) {
		liberarEndereco(empresa->endereco);
		liberarContato(empresa->contato);

		liberarMemoria(&empresa->cnpj);
		liberarMemoria(&empresa->razaoSocial);
		liberarMemoria(&empresa->nomeFantasia);
		liberarMemoria(&empresa->dataAbertura);
		liberarMemoria(&empresa);
	}
}

void liberarListaEmpresas(void* elemento, int posicao) {
	if (elemento != NULL) {
		Empresa* empresa = (Empresa*) elemento;
		liberarEmpresa(empresa);
	}
}

Cliente* criarCliente(const char* nome, const char* cargo, Contato* contato, Empresa* empresa) {
	if (nome == NULL || cargo == NULL || contato == NULL || empresa == NULL) {
		fprintf(stderr, "Erro ao criar novo cliente: parametros nulos\n");
		exit(2);
	}

	Cliente* cliente = alocarMemoria(sizeof(Cliente));

	cliente->nome = duplicarString(nome);
	cliente->cargo = duplicarString(cargo);

	cliente->contato = contato;
	cliente->empresa = empresa;
	cliente->relatorios = criarLista();

	return cliente;
}

void liberarCliente(Cliente* cliente) {
	if (cliente != NULL) {
		liberarContato(cliente->contato);
		liberarEmpresa(cliente->empresa);

		percorrerLista(cliente->relatorios, liberarListaRelatorios);
		liberarLista(cliente->relatorios);

		liberarMemoria(&cliente->nome);
		liberarMemoria(&cliente->cargo);
		liberarMemoria(&cliente);
	}
}

void liberarListaClientes(void* elemento, int posicao) {
	if (elemento != NULL) {
		Cliente* cliente = (Cliente*)elemento;
		liberarCliente(cliente);
	}
}

int converterRegiaoDeString(const char* regiao) {
	if (_stricmp(regiao, "NORTE") == 0) {
		return 0;
	}
	if (_stricmp(regiao, "SUL") == 0) {
		return 1;
	}
	if (_stricmp(regiao, "LESTE") == 0) {
		return 2;
	}
	if (_stricmp(regiao, "OESTE") == 0) {
		return 3;
	}

	return -1;
}

const char* converterStringDeRegiao(Regiao regiao) {
	switch (regiao) {
	case 0:
		return "NORTE";
	case 1:
		return "SUL";
	case 2:
		return "LESTE";
	case 3:
		return "OESTE";
	}

	return NULL;
}
