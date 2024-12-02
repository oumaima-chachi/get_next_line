/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochachi <ochachi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:02:13 by ochachi           #+#    #+#             */
/*   Updated: 2024/12/02 10:51:21 by ochachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_fd(int fd, char *save_data)
{
	char	*buffer;
	int		read_byte;
	char	*tmp;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_byte = 1;
	while (read_byte > 0)
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_byte] = '\0';
		if (!save_data)
			save_data = ft_strdup("");
		if (!save_data)
		{
			free(buffer);
			return (NULL);
		}
		tmp = ft_strjoin(save_data, buffer);
		free(save_data);
		save_data = tmp;
		if (ft_strchr(buffer, '\n'))
			break ;
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
	{
		line[i] = saved_data[i];
		i++;
	}
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
	{
		free(saved_data);
		return (NULL);
	}
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
