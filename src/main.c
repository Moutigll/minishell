/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:19:43 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/22 19:55:03 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_on_error(t_main *main, int error)
{
	free_total(main->head, main, main->cmd_head);
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
	main->lst_var = lst_var;
	main->error = 0;
	copy_env_to_mainstruct(env, main);
	main->env = malloc(sizeof(t_envirronement));
	if (!main->env)
		exit_on_error(main, MALLOC_ERROR);
	main->env->env_list = create_env_list(env);
	main->env->envp = main->g_env;
	print_env(main->env->env_list);
	while_input(main);
	return (0);
}
