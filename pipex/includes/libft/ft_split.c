/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:15:06 by ellucas           #+#    #+#             */
/*   Updated: 2024/10/28 16:39:25 by ellucas          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	countword(const char *s, char c)
{
	size_t	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

char	**freeall(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (0);
}

size_t	ft_deg(const char *s, char c)
{
	size_t	len;

	len = 0;
	if (!ft_strchr(s, c))
		len = ft_strlen(s);
	else
		len = ft_strchr(s, c) - s;
	return (len);
}

char	**ft_split(const char *s, char c)
{
	int		i;
	char	**strs;
	size_t	len;

	strs = (char **)malloc((countword(s, c) + 1) * sizeof(char *));
	if (!s || !strs)
		return (0);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			len = ft_deg(s, c);
			strs[i] = ft_substr(s, 0, len);
			if (!strs[i++])
				return (freeall(strs));
			s += len;
		}
	}
	strs[i] = NULL;
	return (strs);
}
