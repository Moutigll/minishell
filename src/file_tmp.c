/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_tmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:38:03 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/28 14:38:58 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_block(t_head *head)
{
	t_node	*node_tmp;
	t_list	*lst_tmp;
	int		i;

	i = 0;
	lst_tmp = head->head;
	while (lst_tmp)
	{
		node_tmp = lst_tmp->content;
		printf("Block %i\nContent = |%s|\nState = %i\nHead = %i\n", i, node_tmp->content, node_tmp->type, node_tmp->head);
		if (!lst_tmp->next)
			break ;
		lst_tmp = lst_tmp->next;
		printf("\n");
		i++;
	}
}
