/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex_lower.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:50:21 by ellucas           #+#    #+#             */
/*   Updated: 2024/11/21 15:52:49 by ellucas          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printhex_lower(unsigned int nb)
{
	int	i;

	i = 0;
	if (nb >= 16)
	{
		i += ft_printhex_lower(nb / 16);
	}
	ft_printchar("0123456789abcdef"[nb % 16]);
	i++;
	return (i);
}
/*
int ft_printhex_lower(unsigned int nb)
{
	int	i;

	i = 0;
	ft_putnbrhex_lower(nb, &i);
	return (i);
}
*/
