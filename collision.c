#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "headers/types.h"
#include "headers/collision.h"

/* Retourne 1 s'il y a collision entre 2 rectangles
   hitbox.x = largeur, hitbox.y = hauteur */
int collision_rectangles(vect* hitbox1, vect* pos1, vect* hitbox2, vect* pos2){
  return ((pos1 -> x <= pos2 -> x + hitbox2 -> x) &&
	  (hitbox1 -> x + hitbox1 -> x >= hitbox2 -> y) &&
	  (hitbox1 -> y <= hitbox2 -> y + hitbox2 -> y) &&
	  (hitbox1 -> y + hitbox1 -> y >= hitbox2 -> y));
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

void resolution_collision(game* game){
    int jou, enn, bal;
    joueur *jou_prop;
    ennemi *enn_prop;
    balle *bal_prop;

    /* collisions joueurs <-> ennemis */
    for (jou = 0; jou < game -> n_joueurs; jou++){

        jou_prop = &(game -> joueurs[jou]);
        
        for (enn = 0; enn < game -> n_ennemis; enn++){

            if (game -> ennemis[enn].existe){
                
                enn_prop = &(game -> ennemis[enn]);

                if (collision_rectangles(jou_prop -> hitbox, jou_prop -> pos, enn_prop -> hitbox, enn_prop -> pos)){
                    jou_prop -> vie -= DAMAGE_COLLISION;

                    /* joueur meurt */
                    if (jou_prop -> vie == 0){
                        printf("Mort\n");
                        /* pointeur NULL ? Autre chose ? */
                    }
                }
            }
        }
    }

    /* collision avec les balles */
    for (bal = 0; bal < game -> n_balles; bal++){
        
        bal_prop = &(game -> balles[bal]);

        if (bal_prop.existe){

            /* collision balle joueur <-> ennemi */
            if (bal_prop.estJoueur){

                for (enn = 0; enn < game -> n_ennemis; enn++){
                    
                    enn_prop = &(game -> ennemis[enn]);
                    
                    if (enn_prop.existe){

                        if (collision_rectangles(bal_prop -> hit, bal_prop -> pos, enn_prop -> hitbox, enn_prop -> pos)){
                            enn_prop -> vie -= bal_prop -> damage;
                            bal_prop -> existe = 0;
                            reduction_tableau(game, 1);
                              
                            /* ennemi meurt */
                            if (enn_prop -> vie == 0){
                                enn_prop.existe = 0;
                                reduction_tableau(game, 0);
                            }
                        }
                    }
                }
            } else {  /* collision balle ennemi <-> joueur */

                for (jou = 0; jou < game -> n_joueurs; jou++){

                    jou_prop = &(game -> joueurs[jou]);

                    if (collision_rectangles(bal_prop -> hit, bal_prop -> pos, jou_prop -> hitbox, jou_prop -> pos)){
                        jou_prop -> vie -= bal_prop -> damage;
                        bal_prop -> existe = 0;
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