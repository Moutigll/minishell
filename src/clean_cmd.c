/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:19:44 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/23 15:21:38 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleant_tab_cmd(t_head **tab)
{
	t_node	*content;
	t_list	*lst;
	t_list	*tmp;
	int		i;

	i = 0;
	while (tab[i])
	{
		lst = tab[i]->head;
		while (lst)
		{
			content = lst->content;
			free(content->content);
			tmp = lst;
			lst = lst->next;
			free(tmp);
		}
		free(tab[i]);
		i++;
	}
}
