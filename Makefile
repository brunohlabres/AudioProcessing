# Bruno Henrique Labres - GRR20163049
CFLAGS = -Wall -g -fPIC  # gerar "warnings" detalhados e infos de depuração
 
objscomuns = filtros.o trataArq.o trataLinhaDeComando.o
objs = $(objscomuns) wavinfo.o wavrev.o wavvol.o wavautovol.o wavwide.o wavcat.o wavecho.o wavmix.o
objswavinfo = wavinfo.o $(objscomuns)
objswavrev = wavrev.o $(objscomuns)
objswavvol = wavvol.o $(objscomuns)
objswavautovol = wavautovol.o $(objscomuns)
objswavwide = wavwide.o $(objscomuns)
objswavcat = wavcat.o $(objscomuns)
objswavecho = wavecho.o $(objscomuns)
objswavmix = wavmix.o $(objscomuns)
exec = wavinfo wavrev wavvol wavautovol wavwide wavcat wavecho wavmix
 
# regra default (primeira regra)
all: wavinfo wavrev wavvol wavautovol wavwide wavcat wavecho wavmix
 
# regras de ligacao
wavinfo: $(objswavinfo)
wavrev: $(objswavrev)
wavvol: $(objswavvol)
wavautovol: $(objswavautovol)
wavwide: $(objswavwide)
wavcat: $(objswavcat)
wavecho: $(objswavecho)
wavmix: $(objswavmix)
 
# regras de compilação
filtros.o: filtros.c defs.h
trataArq.o: trataArq.c defs.h
trataLinhaDeComando.o: trataLinhaDeComando.c defs.h
wavinfo.o: wavinfo.c filtros.h trataArq.h defs.h trataLinhaDeComando.h
wavrev.o: wavrev.c filtros.h trataArq.h defs.h trataLinhaDeComando.h
wavvol.o: wavvol.c filtros.h trataArq.h defs.h trataLinhaDeComando.h
wavautovol.o: wavautovol.c filtros.h trataArq.h defs.h trataLinhaDeComando.h
wavwide.o: wavwide.c filtros.h trataArq.h defs.h trataLinhaDeComando.h
wavcat.o: wavcat.c filtros.h trataArq.h defs.h trataLinhaDeComando.h
wavecho.o: wavecho.c filtros.h trataArq.h defs.h trataLinhaDeComando.h
wavmix.o: wavmix.c filtros.h trataArq.h defs.h trataLinhaDeComando.h
 
# remove arquivos temporários
clean:
	-rm $(objs) *~
 
# remove tudo o que não for o código-fonte
purge: clean
	-rm $(exec)