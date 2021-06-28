// Bruno Henrique Labres - GRR20163049
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "filtros.h"

void infoWav(tWav wav){
	puts("------------------");
	printf ("Riff Tag: %c%c%c%c\n", wav.ChunkID[0], wav.ChunkID[1], wav.ChunkID[2], wav.ChunkID[3]);
	printf ("Riff Size: %d\n", wav.ChunkSize);
	printf ("Wave Tag: %c%c%c%c\n", wav.Format[0], wav.Format[1], wav.Format[2], wav.Format[3]);
	printf ("Form Tag: %c%c%c%c\n", wav.SubChunk1ID[0], wav.SubChunk1ID[1], wav.SubChunk1ID[2], wav.SubChunk1ID[3]);
	printf ("Format Size: %d\n", wav.SubChunk1Size);
	printf ("Audio Format: %d\n", wav.AudioFormat);
	printf ("Number of Channels: %d\n", wav.NumberOfChannels);
	printf ("Sample Rate: %d\n", wav.SampleRate);
	printf ("Byte Rate: %d\n", wav.ByteRate);
	printf ("Block Align: %d\n", wav.BlockAlign);
	printf ("Bits Per Sample: %d\n", wav.BitsPerSample);
	printf ("Data Tag: %c%c%c%c\n", wav.SubChunk2ID[0], wav.SubChunk2ID[1], wav.SubChunk2ID[2], wav.SubChunk2ID[3]);
	printf ("Data Size: %d\n", wav.SubChunk2Size);
	printf ("Samples/Channel: %d\n", wav.SubChunk2Size/wav.BlockAlign);
	puts("------------------");
}


void wavrev(tWav wav){
	int i;
	int j = 0;
	int16_t *aux; 
	aux = malloc(wav.SubChunk2Size);
	for (i = (wav.SubChunk2Size/2)-1 ; i >= 0 ; i--){
		aux[j] = wav.AudioData[i];
		j++;
	}
	for (i = 0 ; i <= (wav.SubChunk2Size/2)-1 ; i++){
		wav.AudioData[i] = aux[i];
	}
	free (aux);
}

void wavvol(tWav wav, float level){
	int i;
	for (i = 0 ; i <= wav.SubChunk2Size/2 ; i++){
		wav.AudioData[i] = trataClipping(level, wav.AudioData[i]);
	}
}

void wavautovol(tWav wav){
	int i;
	int16_t level = MIN16BITS;
	for (i = 0 ; i <= wav.SubChunk2Size/2 ; i++){
		if (wav.AudioData[i] > level)
		level = wav.AudioData[i];
	}
	level = MAX16BITS/level;
	wavvol(wav, level);
}

void wavwide(tWav wav, float k){
	int i;
	int16_t diff;

	// se o valor nao corresponder a estereo nao funciona
	if (wav.NumberOfChannels != 2){
		fprintf(stderr, "Numero de canais nao compativel para wavwide (nao eh 2).");
		exit(1);
	}

	for (i = 0 ; i <= wav.SubChunk2Size/2 ; i+=2){
		diff = wav.AudioData[i+1] - wav.AudioData[i]; // diff  = R(t) - L(t)
		if (diff < 0) 
			diff = -1;
		else
			diff = 1;
		wav.AudioData[i+1] = wav.AudioData[i+1] + k * diff; // R'(t) = R(t) + k * diff
		wav.AudioData[i] = wav.AudioData[i] - k * diff; // L'(t) = L(t) - k * diff
	}
}

void wavcat(tWav *wav1, tWav wav2){
	uint32_t i, j = 0;

	// samplerates diferentes nao devem prosseguir com o filtro
	if (wav1->SampleRate != wav2.SampleRate){
		fprintf(stderr, "Taxas de amostragem diferentes entre os arquivos.");
		exit(1);
	}

	// numeros de canais diferentes nao devem prosseguir com o filtro
	if (wav1->NumberOfChannels != wav2.NumberOfChannels){
		fprintf(stderr, "Numero de canais diferentes entre os arquivos.");
		exit(1);
	}

	// o trabalho usa apenas PCM 16 bits com sinal, entao
	if (wav1->BitsPerSample != wav2.BitsPerSample){
		fprintf(stderr, "Numero de bits por amostra diferentes entre os arquivos.");
		exit(1);
	}

	wav1->ChunkSize += wav2.ChunkSize - TAMHEADER;
	wav1->SubChunk2Size += wav2.SubChunk2Size;
	wav1->AudioData = (int16_t*) realloc(wav1->AudioData, wav1->SubChunk2Size);
	if (!wav1->AudioData){
		fprintf(stderr, "Erro ao alocar memoria.");
		exit(1);
	}
	for (i = wav1->SubChunk2Size/2 - wav2.SubChunk2Size/2 ; i < wav1->SubChunk2Size/2 ; i++){
		wav1->AudioData[i] = wav2.AudioData[j];
		j++;
	}
	free(wav2.AudioData);
}

void wavecho(tWav wav, float level, float time){
	int i;
	int32_t dist; // quantas posicoes pular no vetor
	int32_t auxClipping;

	dist = (int) (wav.SampleRate * (time/1000.0) * wav.NumberOfChannels);

	for (i = 0 ; i <= wav.SubChunk2Size/2 ; i++){
		if ((i+dist) > wav.SubChunk2Size/2)
			break;

		auxClipping = trataClipping(level, wav.AudioData[i]);
		wav.AudioData[i+dist] = trataClipping(VOLNEUTRO, wav.AudioData[i+dist]+auxClipping);
	}
}

void wavmix(tWav *wav1, tWav *wav2){
	long int i;
	int32_t auxClipping;

	// samplerates diferentes nao devem prosseguir com o filtro
	if (wav1->SampleRate != wav2->SampleRate){
		fprintf(stderr, "Taxas de amostragem diferentes entre os arquivos.");
		exit(1);
	}

	// numeros de canais diferentes nao devem prosseguir com o filtro
	if (wav1->NumberOfChannels != wav2->NumberOfChannels){
		fprintf(stderr, "Numero de canais diferentes entre os arquivos.");
		exit(1);
	}

	// o trabalho usa apenas PCM 16 bits com sinal, entao
	if (wav1->BitsPerSample != wav2->	BitsPerSample){
		fprintf(stderr, "Numero de bits por amostra diferentes entre os arquivos.");
		exit(1);
	}

	if(wav2->SubChunk2Size > wav1->SubChunk2Size){
		wav1->SubChunk2Size = wav2->SubChunk2Size;
		wav1->AudioData = realloc(wav1->AudioData, wav1->SubChunk2Size);
	}
	if (!wav1->AudioData){
		fprintf(stderr, "Erro ao alocar memoria.");
		exit(1);
	}
	for (i = 0 ; i < wav2->SubChunk2Size/2 ; i++){
		auxClipping = wav1->AudioData[i] + wav2->AudioData[i];
		wav1->AudioData[i] = trataClipping(VOLNEUTRO, auxClipping);
	}
	free(wav2->AudioData);
}