/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reattach_head.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 00:12:28 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/10 19:00:22 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_head(t_head *head)
{
	t_list	*lst_tmp;
	t_node	*node;

	if (!head)
		return ;
	while (head->head)
	{
		node = head->head->content;
		free(node->content);
		free(node);
		lst_tmp = head->head;
		head->head = head->head->next;
		free(lst_tmp);
	}
	free(head);
}

static int	is_quote_node(t_node *node)
{
	if (node->type == 0 || node->type == 1)
		return (1);
	return (0);
}

static void	join_and_remove_nodes(t_list *current_node,
	t_list *next_node, t_head *head)
{
	t_node	*node_content;
	t_node	*nxtnode_content;

	node_content = current_node->content;
	nxtnode_content = next_node->content;
	node_content->content = ft_strjoin_free(node_content->content,
			nxtnode_content->content, 1, 1);
	current_node->next = next_node->next;
	free(next_node->content);
	free(next_node);
	head->size--;
}

t_head	*reattach_head(t_head *head)
{
	t_list	*current_node;
	t_list	*next_node;

	if (!head || !head->head)
		return (head);
	current_node = head->head;
	while (current_node && current_node->next)
	{
		next_node = current_node->next;
		if (!((t_node *)next_node->content)->head
			&& is_quote_node(current_node->content)
			&& is_quote_node(next_node->content))
			join_and_remove_nodes(current_node, next_node, head);
		else
			current_node = current_node->next;
	}
	return (head);
}
