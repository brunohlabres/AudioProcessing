// Bruno Henrique Labres - GRR20163049
#ifndef __DEFS__
#define __DEFS__
#include <stdint.h>

#define TAMHEADER (sizeof(tWav) - sizeof (int16_t*))
#define MIN16BITS -32767
#define MAX16BITS 32767
#define SubChunk1SizePADRAO 16 
#define AudioFormatPADRAO 1
#define VOLNEUTRO 1
#define TRUE (1 == 1)
#define FALSE (1 == 0)
#define MIN(a,b) (((a)<(b))?(a):(b))
#define trataClipping(l, valor) ((((l)*(valor)) > (MAX16BITS)) ? (MAX16BITS) : ((((l)*(valor)) < (MIN16BITS)) ? (MIN16BITS) : ((l)*(valor))))

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
	int16_t *AudioData; // amostras de audio 
} tWav;
 
#endif

