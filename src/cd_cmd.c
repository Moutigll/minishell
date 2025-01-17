/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:54:39 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/17 11:58:30 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cd_cmd(t_head *head)
{
	t_head	*head_tmp;
	char	*path;
	int		tmp;


	tmp = check_equal("cd", head, 0);
	if (tmp >= 0)
	{
		head_tmp = return_head(head, tmp);
		path = attach_block(head_tmp);
		if (chdir(path) == -1)
		{
			if (path[0] != '\0')
				printf("%s: No such file or directory\n", path);
		}
		free(head_tmp);
		free(path);
		return (1);
	}
	return (0);
}
