/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:51:36 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/28 14:42:07 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pwd_cmd(char **args)
{
	char	*path;

	if (ft_strcmp(args[0], "pwd") == 0)
	{
		path = getcwd(NULL, 0);
		printf("%s\n", path);
		free(path);
		g_status = 0;
	}
	return (0);
}
