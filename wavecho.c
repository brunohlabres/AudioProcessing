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
	float l, t;

	arqIn = buscaArqEntrada(argc, argv);
	leArquivo(&wav, arqIn);
	t = leTime(argc, argv);
	l = leAten(argc, argv);
	wavecho(wav, l, t);
	arqOut = buscaArqSaida(argc, argv);
	outWav(&wav, arqOut);
}