// Bruno Henrique Labres - GRR20163049
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "defs.h"
#include "trataLinhaDeComando.h"


// busca o arq de entrada na linha de comando
FILE * buscaArqEntrada(int argc, char *argv[]){
	int i;
	FILE * arq;

	for (i = 0 ; i < argc ; i++){
		if (!strcmp(argv[i], "-i")){
			arq = fopen(argv[i+1], "r");
			break;
		}
		else{
			arq = stdin;
		}
	}
	return arq;
}

// busca o destino na linha de comando
FILE * buscaArqSaida(int argc, char *argv[]){
	int i;
	FILE * arq;
	// verifica saida
	for (i = 0 ; i < argc ; i++){
		if (!strcmp(argv[i], "-o")){
			arq = fopen(argv[i+1], "w");
			break;
		}
		else{
			arq = stdout;
		}
	} 
	return arq;
}

float leLevel(int argc, char *argv[]){
	int i;
	float l = -1.0;
	for (i = 0 ; i < argc ; i++){
		if (!strcmp(argv[i], "-l")){
			l = atof(argv[i+1]);
		}
	}
	if ((l < 0.0) || (l > 10.0)){
		fprintf(stderr, "Valor de -l nao permitido, default de 1.0 utilizado.\n");
		l = 1.0;
	}
	return l;
}

// quantidade de wav para concatenar/misturar
int qtdEntradas(int argc, char *argv[]){
	int i = 0;
	// se a saida estiver no inicio da linha de comando
	if (!strcmp(argv[1], "-o"))
		return (argc-3); //num de entradas desconsiderando (desconsiderando nome do prog, "-o" e saida);
	else{
		while (((i+1) < argc) && strcmp(argv[i+1],"-o")){ // cobre o caso de stdin
			i++;
		}
	}
		return i;
}

// como a entrada para mix/cat eh diferente, essa funcao retorna a primeira entrada encontrada na linha de comando
int posicaoPrimeiraEntrada(int argc, char *argv[]){

	// se a saida estiver no inicio da linha de comando
	if (!strcmp(argv[1], "-o"))
		return (3); //desconsiderando nome do prog, "-o" e saida;
	else
		return (1);
}

// busca arq do indice dado
FILE * buscaArqDoIndice(int index, char *argv[]){
	FILE * arq;
	// verifica entrada
	arq = fopen(argv[index], "r");
	if (!arq){
		fprintf(stderr, "Erro ao abrir arquivo.\n");
		exit(1);
	}
	return arq;
}

float leTime(int argc, char *argv[]){
	int i;
	float t = -1.0;
	for (i = 0 ; i < argc ; i++){
		if (!strcmp(argv[i], "-t")){
			t = atof(argv[i+1]);
		}
	}
	if (t < 0.0){
		fprintf(stderr, "Valor de -t nao permitido, default de 1000 ms utilizado.\n");
		t = 1000;
	}
	return t;
}

float leAten(int argc, char *argv[]){
	int i;
	float l = -1.0;
	for (i = 0 ; i < argc ; i++){
		if (!strcmp(argv[i], "-l")){
			l = atof(argv[i+1]);
		}
	}
	if ((l < 0.0) || (l > 1.0)){
		fprintf(stderr, "Valor de -l nao permitido, default de 0.5 utilizado.\n");
		l = 0.5;
	}
	return l;

}