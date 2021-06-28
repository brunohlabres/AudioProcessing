// Bruno Henrique Labres - GRR20163049
#include <stdio.h>
#include "defs.h"
#include "filtros.h"
#include "trataArq.h"
#include "trataLinhaDeComando.h"

int main(int argc, char *argv[]){
	tWav wav1, wav2;
	FILE * arq1;
	FILE * arq2;
	int limite; // limite de ate qual entrada ler
	int cont; // contador da posicao atual de entrada

	
	limite = qtdEntradas(argc, argv); // le quantidade de wav para concatenar
	cont = posicaoPrimeiraEntrada(argc, argv);
	limite += cont; // considera o deslocamento para controlar o while
	arq1 = buscaArqDoIndice(cont, argv); // busca o primeiro arquivo de entrada
	leArquivo(&wav1, arq1); // wav destino fixo
	cont++;
	while (cont < limite){
		arq2 = buscaArqDoIndice(cont, argv); // busca o primeiro arquivo
		leArquivo(&wav2, arq2); // a leitura eh diferente pois a linha de comando tbm eh
		wavcat(&wav1, wav2);
		cont++;
	}
	arq2 = buscaArqSaida(argc, argv);
	outWav(&wav1, arq2);
}