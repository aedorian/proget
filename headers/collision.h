#ifndef _COLLISION_H_
#define _COLLISION_H_

#define DAMAGE_COLLISION 2
#define POWERUP_VIE 2

int collision_rectangles(vect* hitbox1, vect* pos1, vect* hitbox2, vect* pos2);

void reduction_tableau(game *game, int quel_tableau);

void resolution_collisions(game* game);

#endif /* _COLLISION_H_ */
