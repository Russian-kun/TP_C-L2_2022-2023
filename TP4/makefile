FILES := *.o *.gch *.out Chomp Chomp_non_modulaire
COMP  := gcc
COMP_RED := -Wall -Wfatal-errors -fdiagnostics-color=always -g
COMP_FLAGS := $(COMP_RED) -lncurses

Chomp: Chomp.c graphique.o makefile
	$(COMP) Chomp.c graphique.o common.o $(COMP_FLAGS) -o Chomp

graphique.o: graphique.c graphique.h common.o makefile
	$(COMP) -c graphique.c graphique.h common.o $(COMP_FLAGS)

common.o: common.c common.h makefile
	$(COMP) -c common.c common.h $(COMP_FLAGS)

nonmodulaire: makefile
	$(COMP) chomp_nonmodulaire.c $(COMP_FLAGS) -o nonmodulaire
	./nonmodulaire

all: Chomp.c graphique.o common.o common.c common.h graphique.c graphique.h makefile
	make clean
	$(COMP) -c common.c common.h $(COMP_FLAGS)
	$(COMP) -c graphique.c graphique.h common.o $(COMP_FLAGS)
	$(COMP) Chomp.c graphique.o common.o $(COMP_FLAGS) -o Chomp
	$(COMP) chomp_nonmodulaire.c $(COMP_FLAGS) -o nonmodulaire

doc: ./docs makefile

./docs: makefile
	doxygen docs/Doxyfile

clean:
	for file in $(FILES); do \
		if [ -f $$file ]; then \
			rm $$file; \
		fi; \
	done