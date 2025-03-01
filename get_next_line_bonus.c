/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochachi <ochachi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:23:14 by ochachi           #+#    #+#             */
/*   Updated: 2024/12/08 12:03:51 by ochachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_fd(int fd, char *save_data)
{
	char	*buffer;
	int		read_byte;
	char	*tmp;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer || BUFFER_SIZE <= 0)
		return (NULL);
	read_byte = 1;
	while (read_byte > 0 && !ft_strchr(save_data, '\n'))
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte == -1)
			return (free(save_data), free(buffer), NULL);
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
	static char	*stored_data[FOPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	stored_data[fd] = read_fd(fd, stored_data[fd]);
	if (!stored_data[fd])
	{
		return (NULL);
	}
	line = get_line(stored_data[fd]);
	stored_data[fd] = save_r(stored_data[fd]);
	return (line);
}
// int main()
// {
// 	int fd1;
// 	int fd2;
// 	char *line;
// 	fd1 = open("test.txt1",O_RDONLY);
// 	fd2 = open("test.txt2",O_RDONLY);
// 	if (fd1 < 0 || fd2 < 0 )
// 	{
// 		printf("erreur");
// 		return (1);
// 	}
//  while ((line = get_next_line(fd1)) != NULL)
//     {
//         printf("%s\n", line);
//         free(line);
//     }
//     while ((line = get_next_line(fd2)) != NULL)
//     {
//         printf("%s\n", line);
//         free(line);
//     }
// 	close (fd1);
// 	close (fd2);
// 	return (0);
// }