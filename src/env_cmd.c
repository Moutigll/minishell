/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:56:30 by tle-goff          #+#    #+#             */
/*   Updated: 2025/02/04 12:12:46 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	env_cmd(t_list *lst, char **args)
{
	t_env_var	*var;

	while (lst)
	{
		var = lst->content;
		if (var->exported == 1 && var->value[0] != '\0')
		{
			ft_putstr_fd(var->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(var->value, 1);
			ft_putstr_fd("\n", 1);
		}
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (0);
}
