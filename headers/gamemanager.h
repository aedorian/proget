#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include "types.h"

#define NB_WAVES 20

void creer_joueur(joueur* joueur, game* game);
void creer_balle(balle* balle, game* game);
void creer_ennemi(ennemi* ennemi, game* game, vect pos);
void ajouter_balle_obj(game* game, balle balle);
void ajouter_arme_obj(game* game, arme arme);
void ajouter_ennemi_obj(game* game, ennemi ennemi);

void init_partie(game* game, int nb_joueurs);

void ajouter_score(game *game, int score);
void arreter_temps_game(game *game);
void reprendre_temps_game(game *game);

void gerer_waves(game *game, wave_instr waves[WAVES_MAX][WAVES_INSTR_MAX]);
void analyser_ligne_suivante(char ligne[100], char *type_instr, int *pos_x, int *pos_y, ennemi *e, game *game);
void charger_waves_dans_tab(game *game, wave_instr waves[WAVES_MAX][WAVES_INSTR_MAX]);
void charger_mouvement_ennemi(ennemi *e, char* mouvements);

#endif
