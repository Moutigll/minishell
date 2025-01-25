/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:56:30 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/25 16:44:58 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	env_cmd_direct(t_main *main)
{
	int	i;

	i = 0;
	while (main->g_env[i])
	{
		printf("%s\n", main->g_env[i]);
		i++;
	}
}

int	env_cmd(t_head *head, t_main *main)
{
	char	*command;
	int		i;

	i = 0;
	command = attach_block(head);
	if (ft_strncmp((const char *)"env", (const char *)command, 3) == 0)
	{
		if (command[3] != ' ' && command[3] != '\0')
		{
			free(command);
			return (0);
		}
		while (main->g_env[i])
		{
			printf("%s\n", main->g_env[i]);
			i++;
		}
		free(command);
		return (1);
	}
	free(command);
	return (0);
}
