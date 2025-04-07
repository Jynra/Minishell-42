/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uprintnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:04:18 by ellucas           #+#    #+#             */
/*   Updated: 2024/11/21 15:56:25 by ellucas          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_uprintnbr(unsigned int nb)
{
	int	i;

	i = 0;
	if (nb >= 10)
		i += ft_uprintnbr(nb / 10);
	ft_printchar("0123456789"[nb % 10]);
	i++;
	return (i);
}
/*
int	ft_uprintnbr(unsigned int nb)
{
	int	i;

	i = 0;
	ft_uputnbr(nb, &i);
	return (i);
}
*/
