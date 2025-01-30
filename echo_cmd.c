/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:50:32 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/30 15:25:33 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	print_echo(char **args, int block, int flag)
{
	int	i;

	i = 0;
	while (args[block])
	{
		if (i > 0)
			printf(" ");
		printf("%s", args[block]);
		block++;
		i++;
	}
	if (flag == 0)
		printf("\n");
}

static int	check_flag(char *str)
{
	int	i;

	i = 2;
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

	flag = 0;
	block = 0;
	if (ft_strcmp(args[block], "echo") == 0 && args[block][4] == '\0')
	{
		block++;
		if (args[block] != NULL && ft_strncmp(args[block], "-n", 2) == 0
			&& check_flag(args[block]) == 0)
		{
			block++;
			flag = 1;
		}
		print_echo(args, block, flag);
	}
}
