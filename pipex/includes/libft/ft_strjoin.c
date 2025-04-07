/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:38:58 by ellucas           #+#    #+#             */
/*   Updated: 2024/10/18 15:15:05 by ellucas          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	size;
	size_t	i;
	size_t	j;

	if (s1 && s2)
	{
		size = ft_strlen(s1) + ft_strlen(s2);
		str = malloc(size + 1);
		if (str == NULL)
			return (0);
		i = 0;
		while (i < size)
		{
			j = 0;
			while (s1[j] != '\0')
				str[i++] = s1[j++];
			j = 0;
			while (s2[j] != '\0')
				str[i++] = s2[j++];
		}
		str[i] = '\0';
		return (str);
	}
	return (0);
}
