#include "Lecture_fichiers.h"

static int dans_glibc(const char *nom_fichier){
    static const char *glibc[] = {"assert", "complex", "ctype", "errno", "fenv", "float", "inttypes", "iso646", "limits", "locale", "math", "setjmp", "signal", "stdalign", "stdarg", "stdatomic", "stdbool", "stddef", "stdint", "stdio", "stdlib", "stdnoreturn", "string", "tgmath", "threads", "time", "uchar", "wchar", "wctype", "MLV/MLV_all", "stdio_ext"};
    int i;

    assert(nom_fichier != NULL);

    for(i = 0; i < 31; ++i)
        if(!strcmp(glibc[i], nom_fichier))
            return 1;
    return 0;
}

static void supprimer_extension(char *nom_fichier){
    char *extension;

    assert(nom_fichier != NULL);

    extension = strrchr(nom_fichier, '.');
    *extension = '\0';
}

static void lire_inclusions(Tab_dyn *inclusions, FILE *f, char *path_fichier){
    char nom_fichier[500], ligne_dot[2000], ligne_inclusion[1000], nom_fichier_inclus[1000];

    assert(inclusions != NULL);
    assert(f != NULL);
    assert(path_fichier != NULL);


    while(fscanf(f, "%[^\n]\n", ligne_inclusion) == 1){
        sscanf(ligne_inclusion, "#include %*[\"<]%[^.]", nom_fichier_inclus);
        strcpy(nom_fichier, basename(path_fichier));
        supprimer_extension(nom_fichier);
        if(!strcmp(nom_fichier, nom_fichier_inclus))
            continue;
        if(dans_glibc(nom_fichier_inclus))
            continue;
        sprintf(ligne_dot, "%s->%s", nom_fichier, nom_fichier_inclus);
        empiler(inclusions, ligne_dot);
    }
}

void charger_inclusions_fichiers(Tab_dyn *inclusions, FILE *liste_fichiers){
    char path_fichier[300], commande[500];
    FILE *fp;

    assert(inclusions != NULL);
    assert(liste_fichiers != NULL);

    while(fscanf(liste_fichiers, "%s", path_fichier) == 1){
        sprintf(commande, "grep \"#include\" %s", path_fichier);
        fp = popen(commande,"r");
        lire_inclusions(inclusions, fp, path_fichier);
        pclose(fp);
    }
}

FILE *charger_liste_fichiers(const char *path, char type){
    FILE *fp;
    char commande[100];

    assert(path != NULL);

    sprintf(commande, "ls -B -1 %s*.%c 2> /dev/null", path, type);
    fp = popen(commande, "r");
    if(fp == NULL){
        fprintf(stderr, "Erreur lors de... ls ??? Bravo.\n");
        exit(EXIT_SUCCESS); /* Le gars a fait foirer ls. Il a réussi. */
    }
    return fp;
}
