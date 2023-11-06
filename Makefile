CFLAGS = -g -O2 -Wall -Werror `pkg-config --cflags MLV`
LDLIBS = `pkg-config --libs MLV`

prod: affichage.o main.o
	gcc -o prod main.o affichage.o `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` `pkg-config --libs-only-l MLV`
main.o: headers/affichage.h main.c
	gcc -c -W -Wall -std=c89 -pedantic -O2 -D_POSIX_C_SOURCE=199309L main.c
affichage.o: headers/affichage.h affichage.c
	gcc -c -W -Wall -std=c89 -pedantic -O2 -D_POSIC_C_SOURCE=199309L affichage.c
clean:
	rm -rf *.o *~ prod
