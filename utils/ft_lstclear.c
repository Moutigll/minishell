/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:05:10 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/13 13:38:24 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*new_list;

	while (*lst)
	{
		new_list = *lst;
		*lst = (*lst)->next;
		free(new_list->name_var);
		free(new_list->content);
		free(new_list);
	}
}
