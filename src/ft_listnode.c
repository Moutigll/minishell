/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listnode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:00:36 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/19 15:15:35 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_listnode(t_list **lst_tmp, int tab)
{
	while ((*lst_tmp) && tab)
	{
		if (!(*lst_tmp)->next)
			break ;
		(*lst_tmp) = (*lst_tmp)->next;
		tab--;
	}
}
