/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:50:32 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/19 15:24:55 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*echo_command(t_head *head)
{
	int	flag;
	int	tmp;

	flag = 0;
	tmp = check_equal("echo", head, 0);
	if (tmp >= 0)
	{
		tmp = check_equal("-n", head, tmp);
		if (tmp >= 0)
		{
			flag = 1;
			printf("FLAG GOOD\n");
		}
		printf("ECHO GOOD\n");
	}
	return ("COUCOU");
}
