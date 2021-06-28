// Bruno Henrique Labres - GRR20163049
#include <stdio.h>
#include "defs.h"
#include "filtros.h"
#include "trataArq.h"
#include "trataLinhaDeComando.h"

int main(int argc, char *argv[]){
	tWav wav;
	FILE * arqIn; 
	FILE * arqOut;
	float l;

	arqIn = buscaArqEntrada(argc, argv);
	leArquivo(&wav, arqIn);
	l = leLevel(argc, argv);
	wavvol(wav, l);
	arqOut = buscaArqSaida(argc, argv);
	outWav(&wav, arqOut);
}