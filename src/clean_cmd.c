/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:19:44 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/05 18:10:54 by tle-goff         ###   ########.fr       */
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
