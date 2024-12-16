/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:51:22 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/16 11:56:24 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_last_cmd(char *last_cmd, char *command)
{
	int		i;

	i = 0;
	if (last_cmd != NULL)
		free(last_cmd);
	last_cmd = malloc(sizeof(char) * (ft_strlen(command) + 1));
	while (command[i])
	{
		last_cmd[i] = command[i];
		i++;
	}
	last_cmd[i] = '\0';
	return (last_cmd);
}

void	signal_interception(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}
