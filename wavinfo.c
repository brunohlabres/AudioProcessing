// Bruno Henrique Labres - GRR20163049	
#include <stdio.h>
#include "defs.h"
#include "filtros.h"
#include "trataArq.h"
#include "trataLinhaDeComando.h"

int main(int argc, char *argv[]){
	tWav wav;
	FILE * arqIn;

	arqIn = buscaArqEntrada(argc, argv);
	leArquivo(&wav, arqIn);
	infoWav(wav);
}