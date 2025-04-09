/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:48:11 by ellucas           #+#    #+#             */
/*   Updated: 2025/04/09 15:48:13 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executor.h"

/*
** Vérifie si une commande est une commande intégrée (builtin)
*/
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);

	return (
		ft_strcmp(cmd, "echo") == 0 ||
		ft_strcmp(cmd, "cd") == 0 ||
		ft_strcmp(cmd, "pwd") == 0 ||
		ft_strcmp(cmd, "export") == 0 ||
		ft_strcmp(cmd, "unset") == 0 ||
		ft_strcmp(cmd, "env") == 0 ||
		ft_strcmp(cmd, "exit") == 0
	);
}

/*
** Exécute la commande intégrée appropriée
*/
int	execute_builtin(char **args, t_executor *exec)
{
	if (!args || !args[0])
		return (1);

	if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(args[0], "export") == 0)
		return (builtin_export(args, &exec->envp));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (builtin_unset(args, &exec->envp));
	else if (ft_strcmp(args[0], "env") == 0)
		return (builtin_env(exec->envp));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(args, exec));

	return (127);  // Commande non trouvée
}