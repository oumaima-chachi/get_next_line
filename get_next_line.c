/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochachi <ochachi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:02:13 by ochachi           #+#    #+#             */
/*   Updated: 2024/12/01 08:49:19 by ochachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_fd(int fd, char *save_data)
// hadi fontion li katqra lina data mn fd otzid data f string dialna
{
	char *buffer;  // had l buffer howa lighankhazan fih data li bghit nqra
	int read_byte; // hada ghadi igoliya chhal qrit mn bite
	char *tmp;     // hna ghnhato natija dial strjoin dialna
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		return (NULL);
	}
	read_byte = 1;
	while (read_byte > 0)
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		// read katqra lina buffer_size bytes mn fd o kathuthum flbuffer okatruturni chhal mn byte qrat
		if (read_byte == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_byte] = '\0';
		if (!save_data)
		{
			save_data = ft_strdup("");
		}
		tmp = ft_strjoin(save_data, buffer);
		// ghadi ijoini liya save_data oghadi izido ela buffer
		free(save_data); // ghadi ikhwi lia save data
		save_data = tmp; // ohna ghystoqui lina resultat jdida diali
		if (ft_strchr(buffer, '\n'))
		// ila asidi lqiti liya '\n khroj o etini tisae
		{
			break ; // khroj oneal chitan mn l while
		}
		if (save_data && *save_data == '\0')
		{
			free(save_data);
			return (NULL);
		}
	}
	free(buffer);       // ghankhwi ganso hit maendi mandir bih omghnhtajoch
	return (save_data); // returniha kamla azin :)
}
// fonction li ghadi takhd lina line mn saved data
static char	*get_line(char *saved_data)
{
	char	*line;
	int		i;

	if (!saved_data[0]) // ila kant saved data fargha ki raja lina null
	{
		return (NULL);
	}
	i = 0;
	while (saved_data[i] && saved_data[i] != '\n')
	{
		i++; // kihseb size dial line okibqa icounti hta kiwsal l \0 oula \n
	}
	if (saved_data[i] == '\n')
	{
		i++; // ila lqa \0 kizide lina size 1
	}
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
	{
		return (NULL);
	}
	i = 0;
	while (saved_data[i] && saved_data[i] != '\n')
	{
		line[i] = saved_data[i];
		i++;
	}
	if (saved_data[i] == '\n')
	{
		line[i] == saved_data[i];
		i++;
	}
	line = '\0';
	return (line);
}
static char	*save_r(char *saved_data)
{
	char *rmng;
	int i;
	int j;
	i = 0;
	while (saved_data[i] && saved_data != '\n')
	{
		i++;
	}
	if (saved_data == '\n')
	{
		i++;
	}
	rmng = malloc(sizeof(char) * (ft_strlen(saved_data) - i + 1));
	if (!rmng)
	{
		return (NULL);
	}
	j = 0;
	while (saved_data[i])
	{
		rmng[j++] = saved_data[i++];
	}
	rmng[i] = '\0';
	free(saved_data);
	return (rmng);
}
