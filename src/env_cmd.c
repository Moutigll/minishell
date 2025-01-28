/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:56:30 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/28 14:34:30 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	env_cmd(t_list *lst, char **args)
{
	t_env_var	*var;

	if (ft_strcmp(args[0], "env") == 0 && args[0] == NULL)
	{
		while (lst)
		{
			var = lst->content;
			if (var->exported == 1 && var->value[0] != '\0')
				printf("%s=%s\n", var->name, var->value);
			if (!lst->next)
				break ;
			lst = lst->next;
		}
	}
	return (0);
}
