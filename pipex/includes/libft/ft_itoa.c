/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:12:29 by ellucas           #+#    #+#             */
/*   Updated: 2024/10/25 13:19:23 by ellucas          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count(long n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int nb)
{
	char	*str;
	int		c;
	int		neg;
	long	n;

	n = (long)nb;
	c = count(n);
	neg = 0;
	if (n < 0)
	{
		n = n * -1;
		neg = 1;
	}
	str = malloc((c + 1) * sizeof(char));
	if (!str)
		return (0);
	str[c] = '\0';
	while (--c >= 0)
	{
		str[c] = (n % 10) + '0';
		n = n / 10;
	}
	if (neg == 1)
		str[0] = '-';
	return (str);
}
