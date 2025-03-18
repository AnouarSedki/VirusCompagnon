#include "stdlib.h"
#include "stdio.h"
#include "math.h"



void equationSecondDegré(double a,double b,double c) {
    
    FILE *gnuplot = popen("gnuplot -persist","w");

    fprintf(gnuplot, "set title 'Gaphe du second degré'\n");
    fprintf(gnuplot, "set xlabel 'x'\n");
    fprintf(gnuplot, "set ylabel 'f(x)'\n");
    fprintf(gnuplot, "plot %lf*x**2 + %lf*x + %lf title 'f(x) = %.2lfx² + %.2lfx + %.2lf' with lines\n", a, b, c, a, b, c); 
    pclose(gnuplot);

}


int main(void){

    double a;
    double b;
    double c;

    printf("Entrez le premier terme du polynome du second degrés\n");
    scanf("%lf",&a);
    printf("Entrez le deuxieme terme du polynome du second degrés\n");
    scanf("%lf",&b);
    printf("Entrez le troisième terme du polynome du second degrés\n");
    scanf("%lf",&c);

    equationSecondDegré(a,b,c);

    return 0;


}