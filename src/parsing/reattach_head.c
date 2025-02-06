/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reattach_head.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 00:12:28 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/05 14:34:29 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_head(t_list *head);

int	is_quote_node(t_node *node)
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

/*-----------DEBUG--------*/

void	print_head(t_list *head)
{
	t_node	*content;

	while (head)
	{
		content = head->content;
		printf("Node: type:%d | ishead: %d | content: \"%s\"\n",
			content->type, content->head, content->content);
		head = head->next;
	}
}
