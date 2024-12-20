/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:19:43 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/20 17:26:53 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error(char *message, int etat)
{
	if (etat == 0)
		printf("%s\n", message);
}

static void	copy_env_to_mainstruct(char **env, t_main **main)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	(*main)->g_env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		(*main)->g_env[i] = ft_strdup(env[i]);
		i++;
	}
	(*main)->g_env[i] = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_main	*main;

	(void)argc;
	(void)argv;
	main = malloc(sizeof(t_main));
	copy_env_to_mainstruct(env, &main);
	while_input(&main);
	return (0);
}
