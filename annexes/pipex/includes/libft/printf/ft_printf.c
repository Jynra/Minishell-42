/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:34:56 by ellucas           #+#    #+#             */
/*   Updated: 2024/11/21 14:59:38 by ellucas          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	check_type(const char *input, va_list args)
{
	int	i;

	i = 0;
	if (*input == 'c')
		i += ft_printchar(va_arg(args, int));
	else if (*input == 's')
		i += ft_printstr(va_arg(args, char *));
	else if (*input == 'p')
		i += ft_printptr((uintptr_t)va_arg(args, void *));
	else if (*input == 'd')
		i += ft_printint(va_arg(args, int));
	else if (*input == 'i')
		i += ft_printint(va_arg(args, int));
	else if (*input == 'u')
		i += ft_uprintnbr(va_arg(args, int));
	else if (*input == 'x')
		i += ft_printhex_lower(va_arg(args, unsigned int));
	else if (*input == 'X')
		i += ft_printhex_up(va_arg(args, unsigned int));
	else if (*input == '%')
		i += ft_printchar('%');
	return (i);
}

int	ft_printf(const char *input, ...)
{
	int		i;
	va_list	args;

	i = 0;
	va_start (args, input);
	while (*input != '\0')
	{
		if (*input == '%')
		{
			input++;
			i += check_type(input, args);
		}
		else
			i += ft_printchar(*input);
		input++;
	}
	va_end(args);
	return (i);
}
/*
int	main(int ac, char *av[])
{
	ft_printf("result ft_printf is: %c\n", av[1]);
	printf("result printf is : %c\n", av[1]);
}
*/
