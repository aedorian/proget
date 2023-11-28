#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "headers/types.h"
#include "headers/collision.h"

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
void reduction_tableau(game *game, int est_balle_sinon_ennemi){
  int i;
    
  if (est_balle_sinon_ennemi){
    i = game -> n_balles - 1;

    while (game -> balles[i].existe == 0 && i >= 0){
      game -> n_balles -= 1;
      i--;
    }
        
  } else {
    i = game -> n_ennemis - 1;

    while (game -> ennemis[i].existe == 0 && i >= 0){
      game -> n_ennemis -= 1;
      i--;
    }
  }
}

void resolution_collisions(game* game){
  int jou, enn, bal;
  joueur *jou_prop;
  ennemi *enn_prop;
  balle *bal_prop;

  /* collisions joueurs <-> ennemis */
  for (jou = 0; jou < game -> n_joueurs; jou++){ /* pour tous les joueurs */

    jou_prop = &(game -> joueurs[jou]);
        
    for (enn = 0; enn < game -> n_ennemis; enn++){ /* pour tous les ennemis */

      if (game -> ennemis[enn].existe){
                
	enn_prop = &(game -> ennemis[enn]);

	if (collision_rectangles(&(jou_prop -> hitbox), &(jou_prop -> pos), &(enn_prop -> hitbox), &(enn_prop -> pos))){
	  jou_prop -> vie -= DAMAGE_COLLISION;

	  /* joueur meurt */
	  if (jou_prop -> vie <= 0){
	    printf("Mort\n");
	    /* pointeur NULL ? Autre chose ? */
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
	      reduction_tableau(game, 1);
                              
	      /* ennemi meurt */
	      if (enn_prop -> vie <= 0){
		(enn_prop -> existe) = 0;
		reduction_tableau(game, 0);
	      }
	    }
	  }
	}
      } else {  /* collision balle ennemi <-> joueur */

	for (jou = 0; jou < game -> n_joueurs; jou++){

	  jou_prop = &(game -> joueurs[jou]);

	  if (collision_rectangles(&(bal_prop -> hitbox), &(bal_prop -> pos), &(jou_prop -> hitbox), &(jou_prop -> pos))){
	    jou_prop -> vie -= bal_prop -> damage;
	    printf("joueur vie: %d\n", jou_prop -> vie);
	    bal_prop -> existe = 0; /* supprimer la balle */
	    reduction_tableau(game, 1);

	    /* joueur meurt */
	    if (jou_prop -> vie == 0){
	      printf("Mort\n");
	      /* pointeur NULL ? Autre chose ? */
	    }
	  }
	}   
      }
            
    }
  }
}
