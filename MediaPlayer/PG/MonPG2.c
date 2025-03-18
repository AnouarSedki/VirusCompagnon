#include "stdio.h" 
#define pi  3.14159

int main (void) { 
    double rayon , aire ; 

    printf("Veuillez entrer le rayon du cercle : ");
    scanf("%lf",&rayon);
    aire = pi * rayon * rayon ;

    printf("L aire du cercle est : %lf ", aire );

}