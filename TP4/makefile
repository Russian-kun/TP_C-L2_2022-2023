FILES := *.o *.gch *.out Chomp
COMP  := gcc
COMP_RED := -Wall -Wfatal-errors -fdiagnostics-color=always -g
COMP_FLAGS := $(COMP_RED) -lncurses

Chomp: Chomp.c graphique.o common.o makefile
	$(COMP) Chomp.c graphique.o common.o $(COMP_FLAGS) -o Chomp

graphique.o: graphique.c graphique.h common.o makefile
	$(COMP) -c graphique.c graphique.h common.o $(COMP_FLAGS)

common.o: common.c common.h makefile
	$(COMP) -c common.c common.h $(COMP_FLAGS)

clean:
	for file in $(FILES); do \
		if [ -f $$file ]; then \
			rm $$file; \
		fi; \
	done