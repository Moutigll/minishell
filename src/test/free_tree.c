/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:48:18 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/10 18:51:28 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	free_redirection(t_redirection *redir)
{
	if (redir)
	{
		free(redir->file);
		free(redir);
	}
}

void	free_command(t_command *command)
{
	int	i;

	if (!command)
		return ;
	free_tab((void **)command->args);
	if (command->redir)
	{
		i = 0;
		while (i < command->nb_redir)
		{
			free_redirection(command->redir[i]);
			i++;
		}
		free(command->redir);
	}
	free(command);
}

void	free_tree(t_tree *node)
{
	if (!node)
		return ;
	if (node->node_redir->left_type == NODE)
		free_tree(node->node_redir->left);
	else
		free_command(node->node_redir->left);
	if (node->node_redir->right_type == NODE)
		free_tree(node->node_redir->right);
	else
		free_command(node->node_redir->right);
	if (node->redir)
		free_redirection(node->redir);
	free(node->node_redir);
	free(node);
}
