/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:29:24 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/13 13:29:53 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_node(t_list **lst, int index)
{
	t_list	*current;
	t_list	*prev;
	int		i;

	i = 0;
	prev = NULL;
	current = *lst;
	if (current == NULL)
		return ;
	if (index == 0)
	{
		*lst = current->next;
		free(current->name_var);
		free(current->content);
		free(current);
		return ;
	}
	while (current != NULL && i < index)
	{
		prev = current;
		current = current->next;
		i++;
	}
	if (current == NULL)
		return;
	prev->next = current->next;
	free(current->name_var);
	free(current->content);
	free(current);
}
