/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreturnn.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:01:40 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/12 16:51:14 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*lst_returnn(t_list *lst_var, int n)
{
	int	i;

	i = 0;
	while (lst_var && i < n)
	{
		if (!lst_var->next)
			break ;
		lst_var = lst_var->next;
		i++;
	}
	return (lst_var);
}
