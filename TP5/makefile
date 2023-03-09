FILES := *.o *.gch *.out Snake
COMP  := gcc
COMP_RED := -Wall -Wfatal-errors -fdiagnostics-color=always -g
COMP_FLAGS := $(COMP_RED) -lncurses

Snake: Snake.c graphisme.o logique.o makefile
	$(COMP) Snake.c graphisme.o logique.o $(COMP_FLAGS) -o Snake

graphisme.o: graphisme.c graphisme.h makefile
	$(COMP) -c graphisme.c graphisme.h $(COMP_FLAGS)

logique.o: logique.c logique.h makefile
	$(COMP) -c logique.c logique.h $(COMP_FLAGS)

#: common.h makefile
# 	$(COMP) -c common.h $(COMP_FLAGS)

all: Snake makefile graphisme.o logique.o
	make clean
	make Snake

doc: Doxyfile makefile
	doxygen Doxyfile

clean:
	for file in $(FILES); do \
		if [ -f $$file ]; then \
			rm $$file; \
		fi; \
	done