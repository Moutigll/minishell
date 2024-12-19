/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:19:43 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/19 16:10:40 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.h"

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

int	main(int argc, char **env)
{
	t_main	*main;

	(void)argc;
	tester_manager();
	main = malloc(sizeof(t_main));
	copy_env_to_mainstruct(env, &main);
	while_input(&main);
	return (0);
}
