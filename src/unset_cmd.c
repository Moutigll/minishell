/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:07:03 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/12 14:20:22 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	unset_cmd(char *command)
{
	int	i;
	int	j;

	i = 5;
	while_space(command, &i);
	j = search_exist(&command[i]);
	if (j >= 0)
		g_env = ft_realoc_ptr_unset(g_env, j);
}
