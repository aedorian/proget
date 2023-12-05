#ifndef _MANIP_FICH_H_
#define _MANIP_FICH_H_

#define MAX_HIGHSCORE 11

int charger_highscore(highscore t[]);
void ecrire_highscore(highscore t[], int n);
void sauvegarde_highscore(int score, int time);
void charger_sauvegarde(game *game, int num_slot);
void ecrire_sauvegarde(game *game, int num_slot);

#endif /* _MANIP_FICH_H_ */
