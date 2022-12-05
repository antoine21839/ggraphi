#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "Graph.h"
#include "Lecture_fichiers.h"
#include "Tableau_dynamique.h"

int main(int argc, const char **argv){
    int i;
    Tab_dyn incl_src, incl_head;
    FILE *f_src, *f_head;
    const char *path;

    init_tab_dyn(&incl_src);
    init_tab_dyn(&incl_head);
    for(i = 1; i < argc && strcmp("-o", argv[i]); ++i){
        path = argv[i];
        f_src = charger_liste_fichiers(path, 'c');
        f_head = charger_liste_fichiers(path, 'h');
        charger_inclusions_fichiers(&incl_src, f_src);
        charger_inclusions_fichiers(&incl_head, f_head);
        pclose(f_src);
        pclose(f_head);
    }
    cree_pdf(&incl_src, &incl_head, argv[argc - 1]);
    liberer_tab_dyn(&incl_src);
    liberer_tab_dyn(&incl_head);
    return 0;
}
