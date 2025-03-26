#include <stdio.h>
#include <math.h>

#define PI 3.14159
#define POINT_CERCLE 100 

int main(void) {
    double aire,
    double rayon,
    double perimetre,
    double angle,

    FILE *fichier;

    printf("Entrer le rayon du cerlce : ");
    scanf("%lf", &rayon);

    perimetre = 2 * PI * rayon;
    aire = PI * rayon * rayon;

    printf("- Aire en fonction rayon donnée : %.2lf\n", aire);
    printf("- Perimetre en fonction rayon donnée : %.2lf\n", perimetre);

    fichier = fopen("cercle.dat", "w");

    for (int i = 0; i <= POINT_CERCLE; i++) {
        angle = 2 * PI * i / POINT_CERCLE;
        fprintf(fichier, "%lf %lf\n", rayon * cos(angle), rayon * sin(angle));
    }

    fclose(fichier);

    FILE *gnuplot = popen("gnuplot -persist", "w");
    fprintf(gnuplot, "set title 'Cerlce de rayon %.2lf'\n", rayon);
    fprintf(gnuplot, "set size ratio -1\n");
    fprintf(gnuplot, "plot 'cerlce.dat' with lines title 'Cerlce'\n");
    pclose(gnuplot);

    return 0;
}