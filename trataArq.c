// Bruno Henrique Labres - GRR20163049
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "defs.h"
#include "trataArq.h"

// as strings do header nao terminam com '\0'
int comparaStringHeader(uint8_t *s1, char *s2){
	return (s1[0] == s2[0] && s1[1] == s2[1] && s1[2] == s2[2] && s1[3] == s2[3]);
}

//checa se o arq eh um wav
int checaWav(tWav *wav){
	return (comparaStringHeader(wav->ChunkID, "RIFF") && comparaStringHeader(wav->Format, "WAVE")
		&& comparaStringHeader(wav->SubChunk1ID, "fmt ") && comparaStringHeader(wav->SubChunk2ID, "data")
		&& (wav->SubChunk1Size == SubChunk1SizePADRAO) && (wav->AudioFormat == AudioFormatPADRAO)); 
}

void leArquivo(tWav *wav, FILE * arq){
	if (!arq){
		fprintf(stderr, "Erro ao abrir arquivo.");
		exit(1);
	}
	fread (wav, TAMHEADER, 1, arq); // le cabecalho
	if(!checaWav(wav)){
		fprintf (stderr, "O arquivo de entrada nao esta no formato wav.");
		exit(1);
	}
	wav->AudioData = malloc(wav->SubChunk2Size);
	if (!wav->AudioData){
		fprintf(stderr, "Erro ao alocar memoria.");
		exit(1);
	}
	fread (wav->AudioData, wav->SubChunk2Size, 1, arq); // le amostras
	if (arq != stdin){
		fclose(arq);
	}
}

void outWav(tWav *wav, FILE * arq){
	if (!arq){
		fprintf(stderr, "Erro ao abrir arquivo de saida.");
		exit(1);
	}
	fwrite(wav, TAMHEADER, 1, arq);	
	fwrite(wav->AudioData, wav->SubChunk2Size-4, 1, arq);
	if (arq != stdout){
		fclose(arq);
	}
}

