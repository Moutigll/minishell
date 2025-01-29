/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:50:32 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/29 16:06:39 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_flag(char *str)
{
	int	i;

	i = 2;
	if (!str || str[0] != '-' || str[1] != 'n')
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	echo_command(char **args)
{
	int	block;
	int	flag;
	int	i;

	block = 1;
	flag = 0;
	if (args[block] && check_flag(args[block]) == 0)
	{
		block++;
		flag = 1;
	}
	i = 0;
	while (args[block])
	{
		if (i > 0)
			ft_putstr_fd(" ", 1);
		ft_putstr_fd(args[block], 1);
		block++;
		i++;
	}
	if (flag == 0)
		ft_putstr_fd("\n", 1);
	g_status = 0;
}
