// Bruno Henrique Labres - GRR20163049
#ifndef __TRATAARQ__
#define __TRATAARQ__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "defs.h"


int comparaStringHeader(uint8_t *s1, char *s2);
int checaWav(tWav *wav);
void leArquivo(tWav *wav, FILE * arq);
void outWav(tWav *wav, FILE * arq);

#endif

