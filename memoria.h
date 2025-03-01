#pragma once

#include <stdlib.h>

/**************************************************************************************************
* Aloca mem�ria dinamicamente, verificando se a aloca��o foi bem-sucedida e encerrando o programa
* em caso de erro
* @param quantidade Quantidade de bytes a serem alocados
* @return Refer�ncia para a mem�ria alocada
**************************************************************************************************/
void* alocarMemoria(size_t quantidade);

/**************************************************************************************************
* Realoca mem�ria dinamicamente, verificando se a realoca��o foi bem-sucedida e encerrando o 
* programa em caso de erro
* @param referencia Refer�ncia para a mem�ria a ser realocada
* @param quantidade Quantidade de bytes a serem alocados
* @return Refer�ncia para a mem�ria realocada
**************************************************************************************************/
void* realocarMemoria(void* referencia, size_t quantidade);

/**************************************************************************************************
* Libera a mem�ria alocada dinamicamente e anula a refer�ncia
* @param referencia Ponteiro para a refer�ncia da mem�ria a ser liberada
**************************************************************************************************/
void liberarMemoria(void** referencia);

/**************************************************************************************************
* Duplica uma string, alocando mem�ria dinamicamente para a c�pia
* @param string String a ser duplicada
* @return C�pia da string
**************************************************************************************************/
char* duplicarString(const char* string);
