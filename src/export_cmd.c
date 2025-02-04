/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:10:25 by tle-goff          #+#    #+#             */
/*   Updated: 2025/02/04 18:15:04 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	count_tab(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	export_cmd(char **args, t_main *main)
{
	int		i;

	i = 1;
	if (ft_strcmp(args[0], "export") == 0)
	{
		if (count_tab(args) == 1)
			main->error = print_ascii_sorted(main->env->env_list);
		else
		{
			while (args[i])
				check_type_export(args[i++], main->env->env_list);
			update_env(main->env);
			main->error = 0;
		}
	}
	return (0);
}
