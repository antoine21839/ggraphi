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
    char nom_fichier[500], ligne_dot[2000], ligne_inclusion[1000], nom_fichier_inclus[1000], com_prepro[500];

    assert(inclusions != NULL);
    assert(f != NULL);
    assert(path_fichier != NULL);


    while(fscanf(f, "%[^\n]\n", ligne_inclusion) == 1){
        sscanf(ligne_inclusion, "%s %*[\"<]%[^.]", com_prepro, nom_fichier_inclus);
        if(strcmp(com_prepro, "#include"))
            continue;
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
    char path_fichier[1000];
    FILE *f;

    assert(inclusions != NULL);
    assert(liste_fichiers != NULL);

    while(fscanf(liste_fichiers, "%s", path_fichier) == 1){
        f = fopen(path_fichier, "r");
        if(f == NULL)
            fprintf(stderr, "Impossible d'ouvrir \"%s\". Avez vous les permissions de lecture ?\n", path_fichier);
        lire_inclusions(inclusions, f, path_fichier);
        fclose(f);
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
