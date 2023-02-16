COMP  := gcc
COMP_RED := -Wall -Wfatal-errors -fdiagnostics-color=always
COMP_FLAGS := $(COMP_RED) -lncurses

ChronoSimple: ChronoSimple.c common.o
	$(COMP) ChronoSimple.c common.o -o ChronoSimple $(COMP_FLAGS)

ChronoMoyen: ChronoMoyen.c common.o
	$(COMP) ChronoMoyen.c common.o -o ChronoMoyen $(COMP_FLAGS)

common.o : common.h common.c
	$(COMP) -c common.c $(COMP_FLAGS)