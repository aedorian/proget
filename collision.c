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
  /* collision si :   à gauche           et                à droite        et             en haut            et             en bas */
}
