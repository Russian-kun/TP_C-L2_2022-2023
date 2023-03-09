FILES := *.o *.gch *.out Snake
COMP  := gcc
COMP_RED := -Wall -Wfatal-errors -fdiagnostics-color=always -g
COMP_FLAGS := $(COMP_RED) -lncurses -

Snake: Snake.c graphique.o logique.o makefile
	$(COMP) Snake.c graphique.o logique.o $(COMP_FLAGS) -o Snake

graphique.o: graphique.c graphique.h common.o makefile
	$(COMP) -c graphique.c graphique.h common.o $(COMP_FLAGS)

logique.o: logique.c logique.h common.o makefile
	$(COMP) -c logique.c logique.h common.o $(COMP_FLAGS)

common.o: common.h makefile
	$(COMP) -c common.h $(COMP_FLAGS)

all: Snake.c graphique.o logique.o common.o common.c common.h graphique.c graphique.h makefile
	make clean
	$(COMP) -c common.c common.h $(COMP_FLAGS)
	$(COMP) -c graphique.c graphique.h common.o $(COMP_FLAGS)
	$(COMP) -c logique.c logique.h common.o $(COMP_FLAGS)
	$(COMP) Snake.c graphique.o logique.o common.o $(COMP_FLAGS) -o Snake

doc: Doxyfile makefile
	doxygen Doxyfile

clean:
	for file in $(FILES); do \
		if [ -f $$file ]; then \
			rm $$file; \
		fi; \
	done