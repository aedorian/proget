#include "headers/types.h"
#include "headers/affichage.h"
#include <MLV/MLV_all.h>

void creer_fenetre() {
  MLV_create_window("proget", "keyboard events", ECRAN_W, ECRAN_H);
}

void fermer_fenetre() {
  MLV_free_window();
}

void afficher_et_actualiser() {
  
}
