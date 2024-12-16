/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_block_clear.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:05:10 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/16 15:36:07 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lst_block_clear(t_block **lst)
{
	t_block	*new_list;

	while (*lst)
	{
		new_list = *lst;
		*lst = (*lst)->next;
		free(new_list->content);
		free(new_list);
	}
}
