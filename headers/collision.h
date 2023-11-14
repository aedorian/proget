#ifndef _COLLISION_H_
#define _COLLISION_H_

#define DAMAGE_COLLISION 2

int collision_rectangles(vect* hitbox1, vect* pos1, vect* hitbox2, vect* pos2);

void reduction_tableau(game *game, int est_balle_sinon_ennemi);

void resolution_collision(game* game);

#endif /* _COLLISION_H_ */
