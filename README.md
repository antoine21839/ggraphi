# ggraphi
ggraphi, le générateur de graphe d'inclusion open source !

Préface :
Ceci est une version béta. Normalement tout fonctionne, mais pas mal de choses sont à revoir dans le code. 
Le programme "fait confiance" à l'entrée de l'utilisateur, ce qui est évidemment affreux, c'est le moins qu'on puisse dire.
Les assert ne sont pas désactivés. Les flags de compilation contiennent encore "-g". Il est 1:02 du matin et j'ai juste envie de dire que j'ai réussi à faire une version à peu près fonctionnelle avant de me coucher.
Bonne nuit.

Utilisation :
./ggraphi [DOSSIERS] -o [NOM_PDF]

Très stricte ! Le(s) path(s) des dossiers contenant les fichiers de code doivent se terminer par un "/". 
Le nom du pdf doit exister. Le -o doit être placé exactement à l'avant dernière position. Le nom du pdf doit être unique.
