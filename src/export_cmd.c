/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:10:25 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/29 12:33:18 by tle-goff         ###   ########.fr       */
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

int	export_cmd(t_list *lst, char **args, t_main **main)
{
	int		i;

	i = 1;
	if (ft_strcmp(args[0], "export") == 0)
	{
		if (count_tab(args) == 1)
			print_ascii_sorted(lst);
		while (args[i])
			check_type_export(args[i++], lst);
	}
	update_env(main);
	g_status = 0;
	return (0);
}
