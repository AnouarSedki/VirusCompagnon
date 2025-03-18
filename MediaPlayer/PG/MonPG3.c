#include "stdlib.h"
#include "stdio.h"
#include "math.h"

void CourbeSin() {
    
    FILE *gnuplot = popen("gnuplot -persist","w");

    fprintf(gnuplot, "set title 'La courbe de sin(x)'\n");
    fprintf(gnuplot, "set xlabel 'x'\n");
    fprintf(gnuplot, "set ylabel 'f(x)'\n");
    fprintf(gnuplot, "plot sin(x) title 'f(x) = sin(x) \n"); 
    pclose(gnuplot);

}


int main(void){

    CourbeSin();


    return 0;


}