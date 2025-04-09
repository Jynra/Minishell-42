/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 00:24:02 by ellucas           #+#    #+#             */
/*   Updated: 2024/11/22 20:12:32 by ellucas          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	hexconv(uintptr_t n)
{
	int	i;

	i = 0;
	if (n >= 16)
		i += hexconv(n / 16);
	ft_printchar("0123456789abcdef"[n % 16]);
	i++;
	return (i);
}

int	ft_printptr(uintptr_t ptr)
{
	int	i;

	i = 0;
	if (!ptr || ptr == 0)
	{
		write(1, "0x0", 3);
		return (3);
	}
	write(1, "0x", 2);
	i += 2 + hexconv(ptr);
	return (i);
}
