/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:58:53 by ellucas           #+#    #+#             */
/*   Updated: 2024/11/20 18:41:55 by ellucas          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
/*
static void	ft_putchar(char c)
{
	write(1, &c, 1);
}
*/
void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
	{
		ft_printchar('-');
		ft_printchar('2');
		nb = 147483648;
	}
	if (nb < 0)
	{
		ft_printchar('-');
		nb *= -1;
	}
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
	}
	ft_printchar(nb % 10 + 48);
}

int	ft_printint(int n)
{
	int				nb;
	unsigned int	i;

	nb = n;
	i = 1;
	if (n < 0 && n != -2147483648)
	{
		nb = -n;
		i++;
	}
	while (nb > 9)
	{
		nb = nb / 10;
		i++;
	}
	ft_putnbr(n);
	if (n == -2147483648)
		return (11);
	return (i);
}
