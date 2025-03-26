#include "stdlib.h"
#include "stdio.h"
#include "math.h"

void tracerCourbe(int choix) {
    FILE *gnuplot = popen("gnuplot -persist", "w");

    fprintf(gnuplot, "set title 'Représentation des fonctions trigonométriques'\n");
    fprintf(gnuplot, "set xlabel 'x'\n");
    fprintf(gnuplot, "set ylabel 'f(x)'\n");
    fprintf(gnuplot, "set grid\n");
    fprintf(gnuplot, "set key left top\n");
    fprintf(gnuplot, "set xrange [-2*pi:2*pi]\n");
    fprintf(gnuplot, "set yrange [-2:2]\n");
    fprintf(gnuplot, "set zeroaxis\n");

    switch (choix) {
        case 1:
            fprintf(gnuplot, "plot sin(x) title 'sin(x)' lc rgb 'blue' lw 2\n");
            break;
        case 2:
            fprintf(gnuplot, "plot cos(x) title 'cos(x)' lc rgb 'red' lw 2\n");
            break;
        case 3:
            fprintf(gnuplot, "plot tan(x) title 'tan(x)' lc rgb 'green' lw 2 dt 2\n");
            break;
        case 4:
            fprintf(gnuplot, "plot sin(x) title 'sin(x)' lc rgb 'blue' lw 2, "
                             "cos(x) title 'cos(x)' lc rgb 'red' lw 2, "
                             "tan(x) title 'tan(x)' lc rgb 'green' lw 2 dt 2\n");
            break;
    }

    pclose(gnuplot);
}

int main(void) {
    int choix;

    printf("Quelle courbe voulez-vous afficher ?\n");
    printf("1 - sin(x)\n");
    printf("2 - cos(x)\n");
    printf("3 - tan(x)\n");
    printf("4 - Toutes les courbes\n");
    printf("Entrez votre choix : ");
    
    if (scanf("%d", &choix) != 1 || choix < 1 || choix > 4) {
        printf("Entrée invalide. Veuillez entrer un nombre entre 1 et 4.\n");
        return 1;
    }

    tracerCourbe(choix);

    return 0;
}
