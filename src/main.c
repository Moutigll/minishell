/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:39:02 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/16 15:20:51 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char **g_env = NULL;

static int	gest_envp(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	g_env = malloc(sizeof(char *) * (i + 1));
	if (g_env == NULL)
		return (0);
	i = 0;
	while (env[i])
	{
		g_env[i] = ft_strdup(env[i]);
		i++;
	}
	g_env[i] = 0;
	return (1);
}

void	while_main(t_list **lst_var, char **last_cmd, t_block **lst_block)
{
	char	*command;

	while (1)
	{
		command = read_cmd();
		if (command == NULL)
			return ;
		cmd_format(command, lst_var, last_cmd, lst_block);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_block		*lst_block;
	static char	*last_cmd;
	t_list		*lst_var;

	(void)argc;
	(void)argv;
	lst_var = NULL;
	last_cmd = NULL;
	lst_block = NULL;
	if (gest_envp(env) == 0)
		return (0);
	signal(SIGINT, signal_interception);
	signal(SIGQUIT, SIG_IGN);
	while_main(&lst_var, &last_cmd, &lst_block);
	return (0);
}
