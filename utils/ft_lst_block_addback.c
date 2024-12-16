/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_block_addback.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:56:12 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/16 15:05:40 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lst_block_add_back(t_block **lst, t_block *new)
{
	t_block	*new_list;

	if (*lst)
	{
		new_list = ft_lst_block_last(*lst);
		new_list->next = new;
	}
	else
		*lst = new;
}
