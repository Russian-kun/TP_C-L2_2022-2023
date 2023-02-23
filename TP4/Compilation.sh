gcc -c common.c common.h -Wall -Wfatal-errors -fdiagnostics-color=always -lncurses
gcc -c common.o graphique.c graphique.h -Wall -Wfatal-errors -fdiagnostics-color=always -lncurses
gcc Chomp.c common.o graphique.o -Wall -Wfatal-errors -fdiagnostics-color=always -lncurses -o Chomp