#include "stdlib.h"
#include "stdio.h"
#include "math.h"



void equationSecondDegré(double a,double b,double c) {
    
    FILE *gnuplot = popen("gnuplot -persist","w");
    fprintf(gnuplot, "set title 'Polynôme du second degré'\n");
    fprintf(gnuplot, "set xlabel 'x'\n");
    fprintf(gnuplot, "set ylabel 'f(x)'\n");
    fprintf(gnuplot, "plot %lf*x**2 + %lf*x + %lf title 'f(x) = %.2lfx² + %.2lfx + %.2lf' with lines\n", a, b, c, a, b, c);
    fflush(gnuplot);
    pclose(gnuplot);

}


int main(void){

    int a;
    int b;
    int c;

    printf("Entrez le premier terme du polynome du second degrés\n");
    scanf("%d",&a);
    printf("Entrez le deuxieme terme du polynome du second degrés\n");
    scanf("%d",&b);
    printf("Entrez le troisième terme du polynome du second degrés\n");
    scanf("%d",&c);

    equationSecondDegré(a,b,c);

    return 0;


}