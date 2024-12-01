#include "get_next_line.h"
int main()
{
    int fd;             // File descriptor
    char *line;         // Ligne lue
    char *save_data = NULL; // Stocker les données restantes

    // Ouvrir un fichier en mode lecture
    fd = open("example.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Erreur lors de l'ouverture du fichier");
        return (1);
    }

    // Lire et afficher ligne par ligne
    while ((line = read_fd(fd, save_data)) != NULL)
    {
        printf("%s", line);  // Afficher la ligne lue
        free(line);          // Libérer la mémoire de la ligne
    }

    // Fermer le fichier
    close(fd);
    return (0);
}


