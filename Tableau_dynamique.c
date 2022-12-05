#include "Tableau_dynamique.h"

void appliquer_tab_dyn(Tab_dyn *tab, void (*appliquer)(char *)){
    int i;

    assert(tab != NULL);
    assert(appliquer != NULL);

    for(i = 0; i < tab->taille_reelle; ++i)
        appliquer(tab->chaines[i]);
}

void liberer_chaine(char *s){
    assert(s != NULL);

    free(s);
}

void liberer_tab_dyn(Tab_dyn *tab){
    assert(tab != NULL);

    appliquer_tab_dyn(tab, liberer_chaine);
    free(tab->chaines);
}

void init_tab_dyn(Tab_dyn *tab){
    assert(tab != NULL);

    tab->chaines = (char **)malloc(TAILLE_INIT * sizeof(char *));
    if(NULL == tab->chaines){
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire !\n");
        exit(EXIT_FAILURE);
    }
    tab->taille_reelle = 0;
    tab->taille_max = TAILLE_INIT;
}

void empiler(Tab_dyn *tab, const char *s){
    assert(tab != NULL);
    assert(s != NULL);

    if(tab->taille_reelle >= tab->taille_max){
        tab->taille_max *= 2;
        tab->chaines = (char **)realloc(tab->chaines, tab->taille_max * sizeof(char *));
        if(NULL == tab->chaines){
            fprintf(stderr, "Erreur lors de la réallocation de la mémoire !\n");
            exit(EXIT_FAILURE);
        }
    }
    tab->chaines[tab->taille_reelle] = strdup(s);
    if(NULL == tab->chaines[tab->taille_reelle]){
        fprintf(stderr, "Erreur lors de l'ajout d'un élément dans le tableau dynamique !\n");
        exit(EXIT_FAILURE);
    }
    ++(tab->taille_reelle);
}

char *depiler(Tab_dyn *tab){
    char *s;

    assert(tab != NULL);
    assert(tab->taille_reelle >= 0);

    if(tab->taille_reelle == 0)
        return NULL;
    s = tab->chaines[tab->taille_reelle - 1];
    --(tab->taille_reelle);
    return s;
}
