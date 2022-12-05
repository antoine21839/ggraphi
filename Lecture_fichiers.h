#ifndef __LECTURE_FICHIERS__
#define __LECTURE_FICHIERS__

#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include "Tableau_dynamique.h"

void charger_inclusions_fichiers(Tab_dyn *inclusions, FILE *liste_fichiers);
FILE *charger_liste_fichiers(const char *path, char type);

#endif
