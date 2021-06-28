// Bruno Henrique Labres - GRR20163049
#ifndef __TRATALINCOM__
#define __TRATALINCOM__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "defs.h"

FILE * buscaArqEntrada(int argc, char *argv[]);
FILE * buscaArqSaida(int argc, char *argv[]);
float leLevel(int argc, char *argv[]);
int qtdEntradas(int argc, char *argv[]);
int posicaoPrimeiraEntrada(int argc, char *argv[]);
float leTime(int argc, char *argv[]);
float leAten(int argc, char *argv[]);
FILE * buscaArqDoIndice(int index, char *argv[]);

#endif