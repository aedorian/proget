#include <stdio.h>
#include <stdlib.h>
#include "headers/types.h"
#include "headers/manip_fich.h"

int charger_highscore(highscore t[]){
    int score, time, i = 0, n = 0;
    highscore h;
    FILE* fich = NULL;

    if ((fich = fopen("save/highscore.txt", "r")) == NULL){
        printf("Erreur ouverture fichier highscore.txt\n");
        exit(EXIT_FAILURE);
    }

    /* Récupération des score et des temps de jeu */
    while (fscanf(fich, "%d %d", &score, &time) == 2){
        h.score = score;
        h.second = time;
        t[i] = h;  /* Sauvegarde dans t */
        i++;
        n++;
    }

    fclose(fich);

    return n;
}

void ecrire_highscore(highscore t[], int n){
    FILE *fich = NULL;
    int i, n_ajout = n; 
    
    if ((fich = fopen("save/highscore.txt", "w")) == NULL){
        printf("Erreur ouverture fichier highscore\n");
        exit(EXIT_FAILURE);
    }

    /* teste s'il existe 10 records, si oui, alors on sauvegarde que les 10 premiers (10 sauvegardes + celle qu'on tente d'ajouter */
    if (n > 10){
        n_ajout--;
    }

    for (i = 0; i < n_ajout; i++){
        fprintf(fich, "%d %d\n", t[i].score, t[i].second);
    }
    
    fclose(fich);
}

/* tri un tableau de highscore dans l'odre décroissant dont t[0:n-2] trié,
   seul l'éléments de fin est à insérer */
static void tri_insertion_highscore(highscore t[], int n){
    int i;
    highscore h;

    h.score = t[n - 1].score;
    h.second = t[n - 1].second;

    i = n - 1;

    while (i > 0 && t[i-1].score < h.score){
        t[i] = t[i-1];  /* décalage des éléments */
        i--;
    }
    t[i] = h;
}

/* chage les données dans un tableau, ajout du record à ajouter en fin, tri du tableau, écriture, avec suppression, des 10 premiers records */
void sauvegarde_highscore(int score, int time){
    int n;
    highscore t[MAX_HIGHSCORE];
    highscore h;
    
    n = charger_highscore(t);

    h.score = score;
    h.second = time;
    
    t[n] = h;
    n++;

    tri_insertion_highscore(t, n);

    ecrire_highscore(t, n);
}


/* charger le fichier binaire de sauvegarde dans *game  */
void charger_sauvegarde(game *game, int num_slot){
    FILE *fich = NULL;
    size_t s;
    char fichier[18] = "save/sauvegarde_0";

    fichier[16] = num_slot + 48;

    if ((fich = fopen(fichier, "r")) == NULL){
        printf("Erreur ouverture fichier sauvegarde\n");
        exit(EXIT_FAILURE);
    }

    /* game = malloc(sizeof(*game)); */
    s = fread(game, sizeof(*game), 1, fich);

    printf("size: %ld\n", s);

    /* teste ? */

    fclose(fich);
}


/* écriture de la sauvegarde dans un fichier binaire (game) */
void ecrire_sauvegarde(game *game, int num_slot){
    FILE *fich = NULL;
    char fichier[18] = "save/sauvegarde_0";
    char info_fich[20] = "save/info_save0";

    fichier[16] = num_slot + 48;
    
    if ((fich = fopen(fichier, "w")) == NULL){
        printf("Erreur ouverture fichier sauvegarde\n");
        exit(EXIT_FAILURE);
    }

    fwrite(game, sizeof(*game), 1, fich);
    
    fclose(fich);
    
    /* sauvegarder les infos de la save */

    info_fich[14] = num_slot + 48;

    if ((fich = fopen(info_fich, "w+")) == NULL){
        printf("Erreur ouverture fichier d'info sauvegarde\n");
        exit(EXIT_FAILURE);
    }

    fprintf(fich, "%d\n", game -> wave_act);
    fprintf(fich, "%d", game -> score_act.second);

    fclose(fich);
}

void obtenir_info_save(int num_slot, int *wave_nb, int *second) {
  FILE *fich = NULL;
  char info_fich[15] = "save/info_save0";

  info_fich[14] = num_slot + 48;

  if ((fich = fopen(info_fich, "r")) == NULL){
        printf("Erreur ouverture fichier d'info sauvegarde\n");
        exit(EXIT_FAILURE);
  }

  if (fscanf(fich, "%d", wave_nb) < 1 || fscanf(fich, "%d", second) < 1) {
    printf("Erreur lecture fichier d'info sauvegarde\n");
    exit(EXIT_FAILURE);
  }

  fclose(fich);
}
