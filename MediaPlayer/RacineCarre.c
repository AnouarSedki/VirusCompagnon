#include "RacineCarre.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"

float a;
float reponse;

int main(void){

    printf("Entrez un nombre pour calculer la racine carré\n");
    scanf("%f",&a);

    if (a < 0)  {
        printf("Un nombre négatif ne peut pas avoir de racine carré\n");
    }

    else {
        reponse = sqrt(a);
        printf("Voici la racine carré de %f : %f\n",a,reponse);

    }
    return 0;

}
