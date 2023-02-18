FILES := *.o ChronoMoyen ChronoSimple Chrono
COMP  := gcc
COMP_RED := -Wall -Wfatal-errors -fdiagnostics-color=always
COMP_FLAGS := $(COMP_RED) -lncurses

all: ChronoMoyen ChronoSimple Chrono

Chrono: Chrono.c common.o graphique.o
	$(COMP) Chrono.c common.o graphique.o -o Chrono $(COMP_FLAGS)

ChronoSimple: ChronoSimple.c common.o
	$(COMP) ChronoSimple.c common.o -o ChronoSimple $(COMP_FLAGS)

ChronoMoyen: ChronoMoyen.c common.o
	$(COMP) ChronoMoyen.c common.o -o ChronoMoyen $(COMP_FLAGS)

graphique.o : graphique.h graphique.c
	$(COMP) -c graphique.c $(COMP_FLAGS)

common.o : common.h common.c
	$(COMP) -c common.c $(COMP_FLAGS)

clean:
	for file in $(FILES); do \
		if [ -f $$file ]; then \
			rm $$file; \
		fi; \
	done