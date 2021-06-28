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

	arqIn = buscaArqEntrada(argc, argv);
	leArquivo(&wav, arqIn);
	wavrev(wav);
	arqOut = buscaArqSaida(argc, argv);
	outWav(&wav, arqOut);
}