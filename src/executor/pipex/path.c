/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:44:54 by ellucas           #+#    #+#             */
/*   Updated: 2025/04/09 23:57:38 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executor.h"

/*
** Obtient une copie du tableau d'environnement
*/
char	**get_env_array(void)
{
	extern char	**environ;
	char		**env_copy;
	int			i;
	int			count;

	// Compter le nombre de variables d'environnement
	count = 0;
	while (environ[count])
		count++;

	// Allouer le tableau
	env_copy = malloc(sizeof(char *) * (count + 1));
	if (!env_copy)
		return (NULL);

	// Copier chaque variable
	i = 0;
	while (i < count)
	{
		env_copy[i] = ft_strdup(environ[i]);
		if (!env_copy[i])
		{
			free_array(env_copy);
			return (NULL);
		}
		i++;
	}
	env_copy[i] = NULL;

	return (env_copy);
}

/*
** Convertit une structure t_simple_command en tableau d'arguments
*/
char	**convert_simple_command(t_simple_command *simple_cmd)
{
	char	**args;
	int		i;

	// Allouer le tableau d'arguments (+ 1 pour NULL à la fin)
	args = malloc(sizeof(char *) * (simple_cmd->_numberOfArguments + 1));
	if (!args)
		return (NULL);

	// Copier les arguments
	i = 0;
	while (i < simple_cmd->_numberOfArguments)
	{
		args[i] = ft_strdup(simple_cmd->_arguments[i]);
		if (!args[i])
		{
			free_array(args);
			return (NULL);
		}
		i++;
	}
	args[i] = NULL;

	return (args);
}

/*
** Libère un tableau de chaînes de caractères
*/
/*
void	free_array(char **array)
{
	int	i;

	if (!array)
		return;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
*/