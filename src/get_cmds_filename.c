/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds_filename.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:34:54 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/29 17:59:17 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_filename_part1(t_list **lst, t_node **node, int *j, int *start)
{
	char	*filename;

	filename = NULL;
	*node = (*lst)->content;
	if (!(*node)->content[*j])
	{
		(*lst) = (*lst)->next;
		if (!(*lst))
			return (NULL);
		*node = (*lst)->content;
	}
	while ((*node)->content[*j]
		&& ((*node)->content[*j] == '<' || (*node)->content[*j] == '>'))
		(*j)++;
	if ((*node)->content[*j])
	{
		*start = *j;
		while ((*node)->content[*j]
			&& (*node)->content[*j] != '<' && (*node)->content[*j] != '>')
			(*j)++;
		filename = ft_substr((*node)->content, *start, *j - *start);
	}
	else
		filename = ft_strdup("");
	return (filename);
}

char	*get_filename_part2(t_list **lst, t_node *node, int *j, char *filename)
{
	while ((*lst))
	{
		if (node->type != 2)
			filename = ft_strjoin_free(filename, node->content, 1, 0);
		else
		{
			*j = 0;
			while (node->content[*j]
				&& node->content[*j] != '<' && node->content[*j] != '>')
				(*j)++;
			if (node->content[*j] == '<' || node->content[*j] == '>')
			{
				filename = ft_strjoin_free(filename,
						ft_substr(node->content, 0, *j), 1, 1);
				break ;
			}
			filename = ft_strjoin_free(filename, node->content, 1, 0);
			*j = 0;
		}
		(*lst) = (*lst)->next;
		if (!(*lst) || ((t_node *)(*lst)->content)->head == 1)
			break ;
		node = (*lst)->content;
	}
	return (filename);
}

char	*get_filename(t_list **lst, int *j)
{
	t_node	*node;
	char	*filename;
	int		start;

	start = *j;
	filename = get_filename_part1(lst, &node, j, &start);
	if (!filename || (node->content[*j]
			&& (node->content[*j] == '<' || node->content[*j] == '>')))
		return (filename);
	(*lst) = (*lst)->next;
	if (!(*lst))
		return (filename);
	node = (*lst)->content;
	if (node->type == 2 && node->head == 1 && strlen(filename) > 0)
	{
		*j = 0;
		return (filename);
	}
	*j = 0;
	return (get_filename_part2(lst, node, j, filename));
}
