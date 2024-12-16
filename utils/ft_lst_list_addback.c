/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:56:12 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/12 14:56:25 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*new_list;

	if (*lst)
	{
		new_list = ft_lstlast(*lst);
		new_list->next = new;
	}
	else
		*lst = new;
}
