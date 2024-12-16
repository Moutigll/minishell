/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcheckisin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:45:05 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/13 12:01:25 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_lstcheckisin(t_list *lst_var, char *name_var)
{
	int	i;

	i = 0;
	while (lst_var)
	{
		if (ft_strcmp((const char *)lst_var->name_var, (const char *)name_var) == 0)
			return (i);
		if (!lst_var->next)
			break ;
		lst_var = lst_var->next;
		i++;
	}
	return (-1);
}
