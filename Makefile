FLAGS = -W -Wall -std=gnu89 -pedantic -O2
# -D_POSIC_C_SOURCE=199309L

prod: affichage.o evenement.o mouvement.o creation.o gamemanager.o main.o collision.o menu.o manip_fich.o
	gcc -W -Wall -std=c89 -pedantic -O2 -o prod main.o affichage.o evenement.o mouvement.o collision.o creation.o gamemanager.o menu.o manip_fich.o `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` `pkg-config --libs-only-l MLV` -lm
main.o: headers/collision.h headers/affichage.h headers/evenement.h headers/mouvement.h main.c
	gcc -c $(FLAGS) main.c
affichage.o: headers/affichage.h affichage.c
	gcc -c $(FLAGS) affichage.c
collision.o: headers/collision.h collision.c
	gcc -c $(FLAGS) collision.c
evenement.o: headers/evenement.h evenement.c
	gcc -c $(FLAGS) evenement.c -lm
mouvement.o: headers/mouvement.h mouvement.c
	gcc -c $(FLAGS) mouvement.c
creation.o: headers/creation.h creation.c
	gcc -c $(FLAGS) creation.c
gamemanager.o: headers/gamemanager.h gamemanager.c
	gcc -c $(FLAGS) gamemanager.c
menu.o: headers/menu.h menu.c
	gcc -c $(FLAGS) menu.c
manip_fich.o: headers/manip_fich.h manip_fich.c
	gcc -c $(FLAGS) manip_fich.c
clean:
	rm -rf *.o *~ prod
