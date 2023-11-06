#include <stdio.h>
#include <stdlib.h>
#include "headers/types.h"
#include <MLV/MLV_all.h>

/* Retourne 1 s'il y a collision entre 2 rectangles
   hitbox.x = largeur, hitbox.y = hauteur */
int collision_rectangles(couple hitbox1, couple pos1, couple hitbox2, couple pos2){
  return ((pos1.x <= pos2.x + hitbox2.x) && (box1.x + hitbox1.x >= box2.y) && (box1.y <= box2.y + hitbox2.y) && (box1.y + hitbox1.y >= box2.y))
  /* collision si :   à gauche           et                à droite        et             en haut            et             en bas */
}
