#include <stdio.h>
#include <math.h>

#define PI 3.14159

double rayonCercle(){
    double rayon;
    printf("Entrer le rayon du cerle : ");
    scanf("%lf",&rayon);
    return rayon;
}

void parametreCercle(double rayon){
    double angle;
    FILE *fichier;
    double nbPoints = 1000;

    fichier = fopen("cercle.dat", "w");
    for (int i=0; i<=nbPoints;i++) {
        angle = 2*PI*i / nbPoints;
        fprintf(fichier,"%lf %lf\n",rayon*cos(angle),rayon*sin(angle));
    }
    fclose(fichier); 
}
void tracerCercle(double rayon){
    FILE *gnuplot = popen("gnuplot -persist","w");
    fprintf(gnuplot,"plot 'cercle.dat'\n");
    pclose(gnuplot);
}

int main(void) {
    double rayon;
    rayon = rayonCercle();
    parametreCercle(rayon);
    tracerCercle(rayon);
    return 0;
}