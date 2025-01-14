/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:00:55 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/14 13:44:03 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_cmd(t_head *head)
{
	char	*block;
	int		i;

	i  = 0;
	block = attach_block(head);
	while (block[i] && block[i] != ' ')
		i++;
	if (ft_strncmp(block, "exit", 4) == 0 && (block[4] == '\0' || block[4] == ' '))
	{
		clear_history();
		exit(1);
	}
}
