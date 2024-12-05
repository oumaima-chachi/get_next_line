/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochachi <ochachi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:02:13 by ochachi           #+#    #+#             */
/*   Updated: 2024/12/05 20:30:59 by ochachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_fd(int fd, char *save_data)
{
	char	*buffer;
	ssize_t	read_byte;
	char	*tmp;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer || BUFFER_SIZE <= 0)
		return (NULL);
	read_byte = 1;
	while (read_byte > 0 && !ft_strchr(save_data, '\n'))
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte == -1)
			return (free(buffer), NULL);
		buffer[read_byte] = '\0';
		if (!save_data)
			save_data = ft_strdup("");
		if (!save_data)
			return (free(buffer), NULL);
		tmp = ft_strjoin(save_data, buffer);
		free(save_data);
		save_data = tmp;
	}
	free(buffer);
	return (save_data);
}

static char	*get_line(char *saved_data)
{
	char	*line;
	int		i;

	if (!saved_data[0])
		return (NULL);
	i = 0;
	while (saved_data[i] && saved_data[i] != '\n')
		i++;
	if (saved_data[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (saved_data[i] && saved_data[i] != '\n')
	{
		line[i] = saved_data[i];
		i++;
	}
	if (saved_data[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*save_r(char *saved_data)
{
	char	*rmng;
	int		i;
	int		j;

	i = 0;
	while (saved_data[i] && saved_data[i] != '\n')
		i++;
	if (saved_data[i] == '\n')
		i++;
	if (!saved_data[i])
	{
		free(saved_data);
		return (NULL);
	}
	rmng = malloc(sizeof(char) * (ft_strlen(saved_data) - i + 1));
	if (!rmng)
		return (free(saved_data), NULL);
	j = 0;
	while (saved_data[i])
		rmng[j++] = saved_data[i++];
	rmng[j] = '\0';
	free(saved_data);
	return (rmng);
}

char	*get_next_line(int fd)
{
	static char	*stored_data;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stored_data = read_fd(fd, stored_data);
	if (!stored_data)
		return (NULL);
	line = get_line(stored_data);
	stored_data = save_r(stored_data);
	return (line);
}

// #include <stdio.h>

// int main(void)
// {
//     int fd = open("test.txt", O_RDONLY); // Ouvre un fichier prédéfini
//     char *line;

//     if (fd < 0) // Vérifie si l'ouverture a échoué
//     {
//         printf("Erreur: Impossible d'ouvrir le fichier.\n");
//         return (1);
//     }

//     while ((line = get_next_line(fd)) != NULL) // Lit chaque ligne
//     {
//         printf("%s", line); // Affiche la ligne
//         free(line);         // Libère la mémoire allouée pour cette ligne
//     }

//     close(fd); // Ferme le fichier
//     return (0); // Fin du programme
// }