// Bruno Henrique Labres - GRR20163049
#ifndef __FILTROS__
#define __FILTROS__
#include <stdio.h>
#include "defs.h"

void infoWav(tWav wav);
void wavrev(tWav wav);
void wavvol(tWav wav, float l);
void wavautovol(tWav wav);
void wavwide(tWav wav, float k);
void wavcat(tWav *wav1, tWav wav2);
void wavecho(tWav wav, float level, float time);
void wavmix(tWav *wav1, tWav *wav2);

#endif

