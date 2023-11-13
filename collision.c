#include <stdio.h>
#include <stdlib.h>
#include "headers/types.h"
#include <MLV/MLV_all.h>

/* Retourne 1 s'il y a collision entre 2 rectangles
   hitbox.x = largeur, hitbox.y = hauteur */
int collision_rectangles(vect* hitbox1, vect* pos1, vect* hitbox2, vect* pos2){
  return ((pos1 -> x <= pos2 -> x + hitbox2 -> x) &&
	  (hitbox1 -> x + hitbox1 -> x >= hitbox2 -> y) &&
	  (hitbox1 -> y <= hitbox2 -> y + hitbox2 -> y) &&
	  (hitbox1 -> y + hitbox1 -> y >= hitbox2 -> y));
}

void resolution_collision(game* game){
    int jou, enn, bal;
    vect *jou_hit, *jou_pos, *enn_hit, *enn_pos;
    
    for (jou = 0; jou < game -> n_joueurs; jou++){

        jou_hit = &(game -> joueurs[jou].hitbox);
        jou_pos = &(game -> joueurs[jou].pos);
        
        for (enn = 0; enn < game -> n_ennemis; enn++){

            enn_hit = &(game -> ennemis[enn].hitbox);
            enn_pos = &(game -> ennemis[enn].pos);

            /* collisions joueurs <-> ennemis */
            if (collision_rectangles(jou_hit, jou_pos, enn_hit, enn_pos)){
                game -> joueurs[jou].vie -= DAMAGE_COLLISION;

                if (!(game -> joueurs[jou].vie)){
                    
                }
            }
        }
    }
}