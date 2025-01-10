/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:48:44 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/10 19:38:03 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

t_tree	*init_treenode(t_operator operator,
	t_redirection *redir, t_node_redir *node_redir)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->operator = operator;
	node->redir = redir;
	node->node_redir = node_redir;
	return (node);
}

t_node_redir	*init_node_redir(void *left, void *right,
	t_treepoint_type left_type, t_treepoint_type right_type)
{
	t_node_redir	*node;

	node = malloc(sizeof(t_node_redir));
	if (!node)
		return (NULL);
	node->left = left;
	node->right = right;
	node->left_type = left_type;
	node->right_type = right_type;
	return (node);
}

t_redirection	*init_redirection(t_redirection_type type, char *file)
{
	t_redirection	*redirection;

	redirection = malloc(sizeof(t_redirection));
	if (!redirection)
		return (NULL);
	redirection->type = type;
	redirection->file = file;
	return (redirection);
}
