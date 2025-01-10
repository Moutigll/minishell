/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:16:53 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/10 19:05:04 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdlib.h>
#include "libft.h"

typedef enum e_redirection_type
{
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC
}	t_redirection_type;

typedef enum e_operator
{
	NONE,
	AND,
	OR,
	PIPE,
}	t_operator;

typedef enum e_treepoint_type
{
	NODE,
	COMMAND,
}	t_treepoint_type;

typedef struct s_node_redir
{
	void				*left;
	void				*right;
	t_treepoint_type	left_type;
	t_treepoint_type	right_type;
}	t_node_redir;

typedef struct s_redirection
{
	t_redirection_type	type;
	char				*file;
}	t_redirection;

typedef struct s_command
{
	char				**args;
	t_redirection		**redir;
	int					nb_redir;
}	t_command;

typedef struct s_tree
{
	t_operator		operator;
	t_node_redir	*node_redir;
	t_redirection	*redir;
}	t_tree;

// Create tree
t_tree			*init_treenode(t_operator operator,
					t_redirection *redir, t_node_redir *node_redir);
t_node_redir	*init_node_redir(void *left, void *right,
					t_treepoint_type left_type, t_treepoint_type right_type);

// Free tree
void			free_tree(t_tree *node);