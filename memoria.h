#pragma once

#include <stdlib.h>

/**************************************************************************************************
* Aloca memória dinamicamente, verificando se a alocação foi bem-sucedida e encerrando o programa
* em caso de erro
* @param quantidade Quantidade de bytes a serem alocados
* @return Referência para a memória alocada
**************************************************************************************************/
void* alocarMemoria(size_t quantidade);

/**************************************************************************************************
* Realoca memória dinamicamente, verificando se a realocação foi bem-sucedida e encerrando o 
* programa em caso de erro
* @param referencia Referência para a memória a ser realocada
* @param quantidade Quantidade de bytes a serem alocados
* @return Referência para a memória realocada
**************************************************************************************************/
void* realocarMemoria(void* referencia, size_t quantidade);

/**************************************************************************************************
* Libera a memória alocada dinamicamente e anula a referência
* @param referencia Ponteiro para a referência da memória a ser liberada
**************************************************************************************************/
void liberarMemoria(void** referencia);

/**************************************************************************************************
* Duplica uma string, alocando memória dinamicamente para a cópia
* @param string String a ser duplicada
* @return Cópia da string
**************************************************************************************************/
char* duplicarString(const char* string);
