/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex_up.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:31:03 by ellucas           #+#    #+#             */
/*   Updated: 2024/11/20 18:48:06 by ellucas          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putnbrhex_up(unsigned int nb, int *i)
{
	if (nb >= 16)
		ft_putnbrhex_up(nb / 16, i);
	ft_printchar("0123456789ABCDEF"[nb % 16]);
	*i += 1;
}

int	ft_printhex_up(unsigned int nb)
{
	int	i;

	i = 0;
	ft_putnbrhex_up(nb, &i);
	return (i);
}
