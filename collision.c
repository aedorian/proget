#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "headers/types.h"
#include "headers/collision.h"
#include "headers/gamemanager.h"
#include "headers/affichage.h"
#include "headers/evenement.h"
#include "headers/creation.h"

/* Retourne 1 s'il y a collision entre 2 rectangles
   hitbox.x = largeur, hitbox.y = hauteur */
int collision_rectangles(vect* hitbox1, vect* pos1, vect* hitbox2, vect* pos2){
  int x1 = pos1 -> x;
  int x2 = pos2 -> x;
  int y1 = pos1 -> y;
  int y2 = pos2 -> y;
  int hx1 = hitbox1 -> x;
  int hx2 = hitbox2 -> x;
  int hy1 = hitbox1 -> y;
  int hy2 = hitbox2 -> y;

  return ((x2 + hx2 >= x1) &&
	  (x2 <= x1 + hx1) &&
	  (y2 <= y1 + hy1) &&
	  (y2 + hy2 >= y1));
}

/* si est_balle, reduction dans balles, sinon dans ennemis */
void reduction_tableau(game *game, int quel_tableau){
  int i;

  if (quel_tableau == L_BAL){
    i = game -> n_balles - 1;

    /* atteint pas la fin de cette boucle? */
    while (game -> balles[i].existe == 0 && i >= 0){
      game -> n_balles -= 1;
      i--;
    }
        
  } else if (quel_tableau == L_ENN) {
    i = game -> n_ennemis - 1;

    while (game -> ennemis[i].existe == 0 && i >= 0){
      game -> n_ennemis -= 1;
      i--;
    }
  } else if (quel_tableau == L_JOU) {
    printf("REDUCTION TABLEAU JOUEURS\n");
    i = game -> n_joueurs - 1;
    printf("i=%d\n", i);
    /* game -> n_joueurs = 0; */

    while (game -> joueurs[i].existe == 0 && i >= 0){
      /*if (game -> joueurs[i].existe) {
	game -> n_joueurs += 1;
      }*/
      game -> n_joueurs -= 1;
      printf("etape\n");
      i--;
    }

    printf("N_JOUEURS = %d\n", game -> n_joueurs);
  }
}

void resolution_collisions(game* game){
  int jou, enn, bal;
  joueur *jou_prop;
  ennemi *enn_prop;
  balle *bal_prop;
  int arme_random;

  /* collisions joueurs <-> ennemis */
  for (jou = 0; jou < game -> n_joueurs; jou++){ /* pour tous les joueurs */

    jou_prop = &(game -> joueurs[jou]);
        
    for (enn = 0; enn < game -> n_ennemis; enn++){ /* pour tous les ennemis */

      if (game -> ennemis[enn].existe){
                
	enn_prop = &(game -> ennemis[enn]);

	if (collision_rectangles(&(jou_prop -> hitbox), &(jou_prop -> pos), &(enn_prop -> hitbox), &(enn_prop -> pos)) && jou_prop -> existe){

	  enn_prop -> vie -= 1;
	  printf("ennemi vie: %d\n", enn_prop -> vie);
                              
	  /* ennemi meurt: ni powerup ni score */
	  if (enn_prop -> vie <= 0){
	    (enn_prop -> existe) = 0;
	    reduction_tableau(game, L_ENN);
	  }
	}
      }
    }
  }

  /* collision avec les balles */
  for (bal = 0; bal < game -> n_balles; bal++){ /* pour toutes les balles */
        
    bal_prop = &(game -> balles[bal]);

    if (bal_prop -> existe){

      if (bal_prop -> estJoueur){ /* collision balle joueur <-> ennemi */

	for (enn = 0; enn < game -> n_ennemis; enn++){
                    
	  enn_prop = &(game -> ennemis[enn]);
                    
	  if (enn_prop -> existe){

	    if (collision_rectangles(&(bal_prop -> hitbox), &(bal_prop -> pos), &(enn_prop -> hitbox), &(enn_prop -> pos))){
	      enn_prop -> vie -= bal_prop -> damage;
	      printf("ennemi vie: %d\n", enn_prop -> vie);
	      bal_prop -> existe = 0; /* supprimer la balle */
	      reduction_tableau(game, L_BAL);
                              
	      /* ennemi meurt */
	      if (enn_prop -> vie <= 0){
	        /* drop un powerup à la position de l'ennemi */
		drop_powerup(game, enn_prop -> pos.x, enn_prop -> pos.y);
		(enn_prop -> existe) = 0;
		reduction_tableau(game, L_ENN);
		/* ajouter au score */
		ajouter_score(game, 100);
	      }
	    }
	  }
	}
      } else {  /* collision balle ennemi <-> joueur */

	for (jou = 0; jou < game -> n_joueurs; jou++){

	  jou_prop = &(game -> joueurs[jou]);

	  if (collision_rectangles(&(bal_prop -> hitbox), &(bal_prop -> pos), &(jou_prop -> hitbox), &(jou_prop -> pos)) && jou_prop -> existe){
	    
	    if (bal_prop -> powerup == 1) { /* vie */
	      jou_prop -> vie += POWERUP_VIE;
	      if (jou_prop -> vie > J_VIE_INIT) {
		jou_prop -> vie = J_VIE_INIT;
	      }
	      
	    } else if (bal_prop -> powerup == 2) { /* arme */
	      /* sélectionner une arme différente */
	      do {
		arme_random = rand() % 5;
	      } while (arme_random == jou_prop -> arme.id_arme);
	      jou_prop -> arme = game -> armes_obj[arme_random];
	    } else { /* balle normale */
	      jou_prop -> vie -= bal_prop -> damage;
	      printf("joueur vie: %d\n", jou_prop -> vie);
	    }
	    
	    bal_prop -> existe = 0; /* supprimer la balle */
	    reduction_tableau(game, L_BAL);

	    /* joueur meurt */
	    if (jou_prop -> vie <= 0){
	      (jou_prop -> existe) = 0;
	      reduction_tableau(game, L_JOU); /* réduire le tableau des joueurs */
	      printf("Mort\n");
	      if (game -> n_joueurs == 0) {
		printf("Tout le monde est dead\n");
		arreter_temps_game(game);
		game -> wc = NOM_WAVE_T;
	      }
	    }
	  }
	}   
      }
            
    }
  }
}
