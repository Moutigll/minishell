/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:51:36 by tle-goff          #+#    #+#             */
/*   Updated: 2025/02/05 14:55:36 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pwd_cmd(char **args, t_envirronement *env)
{
	char	*path;

	if (ft_strcmp(args[0], "pwd") == 0)
	{
		path = get_env_value(env->envp, "PWD");
		printf("%s\n", path);
	}
	update_env(env);
	return (0);
}
