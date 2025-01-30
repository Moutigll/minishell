/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:51:36 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/30 20:25:20 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pwd_cmd(char **args, char **env)
{
	char	*path;

	if (ft_strcmp(args[0], "pwd") == 0)
	{
		path = get_env_value(env, "PWD");
		printf("%s\n", path);
		g_status = 0;
	}
	return (0);
}
