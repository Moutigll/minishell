/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:19:43 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/30 17:00:37 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile int g_status = 0;

void	exit_on_error(t_main *main, int error)
{
	free_total(main, main->cmd_head);
	exit(error);
}

void	error(char *message, int etat)
{
	if (etat == 0)
		printf("%s\n", message);
}

static void	copy_env_to_mainstruct(char **env, t_main *main)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	main->g_env = malloc(sizeof(char *) * (i + 1));
	if (!main->g_env)
		exit_on_error(main, MALLOC_ERROR);
	i = 0;
	while (env[i])
	{
		main->g_env[i] = ft_strdup(env[i]);
		if (!main->g_env[i])
			exit_on_error(main, MALLOC_ERROR);
		i++;
	}
	main->g_env[i] = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_list	*lst_var;
	t_main	*main;

	(void) argc;
	(void) argv;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	lst_var = NULL;
	main = malloc(sizeof(t_main));
	if (!main)
		return (MALLOC_ERROR);
	main->path = NULL;
	main->error = 0;
	copy_env_to_mainstruct(env, main);
	main->env = malloc(sizeof(t_envirronement));
	if (!main->env)
		exit_on_error(main, MALLOC_ERROR);
	main->env->env_list = create_env_list(env);
	main->env->envp = main->g_env;
	while_input(main);
	return (0);
}
