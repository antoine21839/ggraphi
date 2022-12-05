#include "Graph.h"
#include "Tableau_dynamique.h"
#include <stdlib.h>

static void ecrire_debut(FILE *f_dot){
    assert(f_dot != NULL);

    fprintf(f_dot, "digraph D {\n");
}

static void ecrire_inclusions(FILE *f_dot, Tab_dyn *inclusions, const char *style){
    char *ligne_inclusion;

    assert(f_dot != NULL);
    assert(inclusions != NULL);

    while((ligne_inclusion = depiler(inclusions)) != NULL){
        fprintf(f_dot, "\t%s [style=\"%s\"];\n", ligne_inclusion, style);
        free(ligne_inclusion);
    }
}

static void ecrire_fin(FILE *f_dot){
    assert(f_dot != NULL);

    fprintf(f_dot, "}\n");
}

static void dessine_graph(FILE *f_dot, Tab_dyn *inc_src, Tab_dyn *inc_head){
    assert(f_dot != NULL);
    assert(inc_src != NULL);
    assert(inc_head != NULL);

    ecrire_debut(f_dot);
    ecrire_inclusions(f_dot, inc_src, "dotted");
    ecrire_inclusions(f_dot, inc_head, "filled");
    ecrire_fin(f_dot);
}

void cree_pdf(Tab_dyn *inc_src, Tab_dyn *inc_head, const char *nom_pdf){
    FILE *out;
    char commande[100];

    assert(inc_src != NULL);
    assert(inc_head != NULL);
    assert(NULL != nom_pdf);

    sprintf(commande, "dot -Tpdf -o %s", nom_pdf);
    /* sprintf(commande, "cat"); */ /* pour débugger */
    out = popen(commande, "w");
    if(NULL == out){
        fprintf(stderr, "Erreur lors de l'ouverture du pipe de sortie vers la commande \"%s\" !\n", commande);
        exit(EXIT_FAILURE);
    }
    dessine_graph(out, inc_src, inc_head);
    pclose(out);
}
