/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:16:40 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/13 13:57:59 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

//($&&$)>$||($>>$&&$<$)
//(($||($&&$)|$&&($||$))
t_redirection_type get_redirection_type(char *str)
{
	if (str[0] == '<' && str[1] == '<')
		return (HEREDOC);
	else if (str[0] == '>' && str[1] == '>')
		return (APPEND);
	else if (str[0] == '<')
		return (INPUT);
	else if (str[0] == '>')
		return (OUTPUT);
	return (REDIR_NONE);
}

t_tree *construct_tree(char *str, char ***tab)
{
	int i = 0;
	int prev_files = 0;
	t_tree *root = init_treenode(OP_NONE, NULL, NULL);
	t_tree *current_node = root;

   
	return root;
}

void print_tree(t_tree *node, int depth)
{
	if (!node)
		return ;
	for (int i = 0; i < depth; i++)
		printf("\t");
	if (node->operator == AND)
		printf("AND\n");
	else if (node->operator == OR)
		printf("OR\n");
	else if (node->operator == PIPE)
		printf("PIPE\n");
	else if (node->operator == BRACKET)
		printf("BRACKET\n");
	else
		printf("NONE\n");
	if (node->redir)
	{
		if (node->redir->type == INPUT)
			printf("\tINPUT -> %s\n", node->redir->file);
		else if (node->redir->type == OUTPUT)
			printf("\tOUTPUT -> %s\n", node->redir->file);
		else if (node->redir->type == APPEND)
			printf("\tAPPEND -> %s\n", node->redir->file);
		else if (node->redir->type == HEREDOC)
			printf("\tHEREDOC -> %s\n", node->redir->file);
	}
	if (node->node_redir)
	{
		if (node->node_redir->left)
			print_tree(node->node_redir->left, depth + 1);
		if (node->node_redir->right)
			print_tree(node->node_redir->right, depth + 1);
	}
}

int main()
{
	char *str = "($&&$)>$||($>>$&&$<$)";
	char ***tab = NULL;  

	t_tree *tree = construct_tree(str, tab);
	print_tree(tree, 0);

	return 0;
}