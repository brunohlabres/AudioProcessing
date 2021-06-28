#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define TAMHEADER (sizeof(tWav) - sizeof (uint8_t*))

typedef struct tWav{
	uint8_t ChunkID[4]; // "RIFF" // identifica o arquivo 
	uint32_t ChunkSize; // filesize-8 // tamanho do arquivo sem considerar este chunk
	uint8_t Format[4]; // "WAVE" // define o formato interno
	uint8_t SubChunk1ID[4]; // "fmt" // cabecalho deste chunk
	uint32_t SubChunk1Size; // 16 para PCM // tamanho deste chunk
	uint16_t AudioFormat; // 1 para PCM // indica a codificacao utilizada 
	uint16_t NumberOfChannels; // numero de canais de audio
	uint32_t SampleRate; // Taxa de amostragem (amostras por seg) 
	uint32_t ByteRate; // Taxa de bytes por segundo
	uint16_t BlockAlign; // numero de bytes por amostra (soma de todos os canais)
	uint16_t BitsPerSample; // bits de amostra, por canal 
	uint8_t SubChunk2ID[4]; // "data" // cabeçalho de chunk
	uint32_t SubChunk2Size; // numero de bytes de dados (amostras)
	uint8_t *AudioData; // amostras de audio 
} tWav;

void leArquivo(int argc, char *argv[], tWav *wav){
	int i;
	FILE * arq;
	// verifica entrada
	for (i = 0 ; i < argc ; i++){
		if (!strcmp(argv[i], "-i")){
			arq = fopen(argv[i+1], "r");
			break;
		}
		else{
			arq = stdin;
		}
	}
	if (!arq){
		puts("Erro ao abrir arquivo.");
		exit(1);
	}

	fread (wav, TAMHEADER, 1, arq); // le cabecalho
	wav->AudioData = malloc(wav->SubChunk2Size);
	fread (wav->AudioData, wav->SubChunk2Size, 1, arq); // le amostras
}

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
	printf ("Samples/Channel: %d\n", wav.SubChunk2Size/wav.BlockAlign); //checar (?)
	puts("------------------");
}

void outWav(int argc, char *argv[], tWav *wav){
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
	fwrite(wav, TAMHEADER, 1, arq);
	fwrite(wav->AudioData, wav->SubChunk2Size-4, 1, arq); //(?) -4 
}

int main(int argc, char *argv[]){
	tWav wav;

	leArquivo(argc, argv, &wav);
	infoWav(wav);
	//outWav(argc, argv, &wav);
}