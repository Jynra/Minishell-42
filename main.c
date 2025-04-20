/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:57:15 by ellucas           #+#    #+#             */
/*   Updated: 2025/04/20 19:32:28 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/parser.h"

/*
int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    
    // Code temporaire jusqu'à l'implémentation complète
    printf("Minishell en cours de développement\n");
    return (0);
}
*/

int main(int argc, char **argv)
{
    char *line;
    t_command *cmd_table;
    
    (void)argc;
    (void)argv;
    
    while (1)
    {
        line = readline("minishell> ");
        if (!line)
            break;
            
        if (*line)
            add_history(line);
            
        cmd_table = create_command();
        if (!cmd_table)
        {
            free(line);
            continue;
        }
        
        if (parse_line(line, cmd_table) == 0)
            execute_command(cmd_table);
            
        free_command(cmd_table);
        free(line);
    }
    
    return (0);
}
