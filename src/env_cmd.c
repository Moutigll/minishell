/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:56:30 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/08 11:35:27 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	env_cmd(t_head *head, t_main **main)
{
	char	*command;
	int		i;

	i = 0;
	command = attach_block(head);
	if (ft_strncmp((const char *)"env", (const char *)command, 3) == 0)
	{
		if (command[3] != ' ' && command[3] != '\0')
			return (0);
		while ((*main)->g_env[i])
		{
			printf("%s\n", (*main)->g_env[i]);
			i++;
		}
		return (1);
	}
	return (0);
}