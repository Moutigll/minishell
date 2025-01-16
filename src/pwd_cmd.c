/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:06:49 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/16 16:16:54 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pwd_cmd(t_head *head)
{
	char	*attach;
	char	*path;
	int		tmp;

	tmp = check_equal("pwd", head, 0);
	if (tmp < 0)
		return (0);
	attach = attach_block(return_head(head, tmp));
	if (ft_strlen((const char *)attach) > 0)
		return (printf("pwd: too many arguments\n"), 1);
	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
	return (1);
}
