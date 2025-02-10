/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:50:32 by tle-goff          #+#    #+#             */
/*   Updated: 2025/02/10 17:58:10 by tle-goff         ###   ########.fr       */
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

int	echo_command(char **args)
{
	int	block;
	int	flag;
	int	i;

	block = 1;
	flag = 0;
	while (args[block] && check_flag(args[block]) == 0)
	{
		block++;
		flag = 1;
	}
	i = 0;
	while (args[block])
	{
		if (i > 0)
			ft_putstr_fd(" ", STDOUT_FILENO);
		ft_putstr_fd(args[block], STDOUT_FILENO);
		block++;
		i++;
	}
	if (flag == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
