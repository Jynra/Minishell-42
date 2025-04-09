/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:47:53 by ellucas           #+#    #+#             */
/*   Updated: 2025/04/09 15:47:57 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executor.h"

/*
** Vérifie si l'argument est l'option -n
*/
static int	is_n_option(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);

	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/*
** Implémente la commande builtin echo
** echo avec option -n: n'affiche pas de newline à la fin
*/
int	builtin_echo(char **args)
{
	int	i;
	int	n_option;

	n_option = 0;
	i = 1;

	// Vérifier l'option -n
	while (args[i] && is_n_option(args[i]))
	{
		n_option = 1;
		i++;
	}

	// Afficher les arguments
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}

	// Ajouter nouvelle ligne si pas d'option -n
	if (!n_option)
		ft_putchar_fd('\n', STDOUT_FILENO);

	return (0);
}