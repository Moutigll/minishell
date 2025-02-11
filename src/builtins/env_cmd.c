/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:56:30 by tle-goff          #+#    #+#             */
/*   Updated: 2025/02/10 22:04:16 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	env_cmd(t_list *lst, char **args)
{
	t_env_var	*var;

	while (lst)
	{
		if (args[1] != (void *)0)
			return (127);
		var = lst->content;
		if (var->exported == 1 && var->name[0] != '\0')
			printf("%s=%s\n", var->name, var->value);
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (0);
}
