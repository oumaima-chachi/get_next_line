/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochachi <ochachi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:01:53 by ochachi           #+#    #+#             */
/*   Updated: 2024/11/29 14:14:39 by ochachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
	{
		return (0);
	}
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
char	*ft_strjoin(const char *s1, const char *s2)
{
	int		len;
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
	{
		return (NULL);
	}
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (c == '\0')
	{
		return ((char *)&s[i]);
	}
	return (NULL);
}
char	*ft_strdup(char *s)
{
	char	*dup;
	size_t	i;

	i = 0;
	if (!s)
	{
		return (NULL);
	}
	dup = malloc(ft_strlen(s) + 1);
	if (!dup)
	{
		return (NULL);
	}
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
// char	*ft_substr(char *s, unsigned int start, size_t len)
// {
// 	size_t	taille_s;
// 	char	*sub;
// 	size_t	i;

// 	if (start >= ft_strlen(s))
// 	{
// 		return (ft_strdup(""));
// 	}
// 	taille_s = ft_strlen(s);
// 	if (len > taille_s - start)
// 	{
// 		len = taille_s - start;
// 	}
// 	sub = malloc(sizeof(char) * (len + 1));
// 	if (!sub)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 		sub[i++] = s[start++];
// 	sub[i] = '\0';
// 	return (sub);
// }
