CFLAGS = -g -O2 -Wall -Werror `pkg-config --cflags MLV`
LDLIBS = `pkg-config --libs MLV`

prod: collision.o affichage.o evenement.o mouvement.o creation.o gamemanager.o main.o
	gcc -W -Wall -std=c89 -pedantic -O2 -o prod main.o affichage.o evenement.o mouvement.o collision.o creation.o gamemanager.o `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` `pkg-config --libs-only-l MLV`
main.o: headers/collision.h headers/affichage.h headers/evenement.h headers/mouvement.h main.c
	gcc -c -W -Wall -std=c89 -pedantic -O2 -D_POSIX_C_SOURCE=199309L main.c
affichage.o: headers/affichage.h affichage.c
	gcc -c -W -Wall -std=c89 -pedantic -O2 -D_POSIC_C_SOURCE=199309L affichage.c
collision.o: headers/collision.h collision.c
	gcc -c -W -Wall -std=c89 -pedantic -O2 -D_POSIC_C_SOURCE=199309L collision.c
evenement.o: headers/evenement.h evenement.c
	gcc -c -W -Wall -std=c89 -pedantic -O2 -D_POSIC_C_SOURCE=199309L evenement.c
mouvement.o: headers/mouvement.h mouvement.c
	gcc -c -W -Wall -std=c89 -pedantic -O2 -D_POSIC_C_SOURCE=199309L mouvement.c
creation.o: headers/creation.h creation.c
	gcc -c -W -Wall -std=c89 -pedantic -O2 -D_POSIC_C_SOURCE=199309L creation.c
gamemanager.o: headers/gamemanager.h gamemanager.c
	gcc -c -W -Wall -std=c89 -pedantic -O2 -D_POSIC_C_SOURCE=199309L gamemanager.c
clean:
	rm -rf *.o *~ prod
