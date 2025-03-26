#include <stdio.h>
#include <stdlib.h>

int main() {
    // Tableau avec 5 images dans le dossier "images/"
    const char *image_files[] = {
        "images/image1.jpg",
        "images/image2.jpg",
        "images/image3.jpg",
        "images/image4.jpg",
        "images/image5.jpg"
    };

    // Afficher chaque image avec un délai de 2 secondes
    for (int i = 0; i < 5; i++) {
        char command[100];
        snprintf(command, sizeof(command), "xdg-open %s", image_files[i]); // Création de la commande

        printf("Affichage de : %s\n", image_files[i]);
        system(command); // Exécuter la commande

        sleep(2); // Attendre 2 secondes avant l'image suivante
    }

    return 0;
}
