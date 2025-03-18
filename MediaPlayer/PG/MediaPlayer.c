#include "stdio.h"
#include "stdlib.h"


void AfficherImage(const char *LienDuFichier) {
    char commande[256];
    snprintf(commande,sizeof(commande),"eog %s",LienDuFichier);
    system(commande);
}

int main(){
    AfficherImage("../images/image1.jpeg");
    return 0;
}