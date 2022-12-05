#ifndef __TABLEAU_DYNAMIQUE__
#define __TABLEAU_DYNAMIQUE__

#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#define TAILLE_INIT 3

typedef struct{
    int taille_reelle;
    int taille_max;
    char **chaines;
}Tab_dyn;

void appliquer_tab_dyn(Tab_dyn *tab, void (*appliquer)(char *));
void liberer_tab_dyn(Tab_dyn *tab);
void init_tab_dyn(Tab_dyn *tab);
void empiler(Tab_dyn *tab, const char *s);
char *depiler(Tab_dyn *tab);

#endif
