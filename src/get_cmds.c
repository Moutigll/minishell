/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 00:55:00 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/23 15:25:08 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_pipe_segment(t_head **current_head, t_node *content, int *start, int j)
{
	if (j != *start)
	{
		if (add_before_pipe(&(*current_head)->head, content->head,
				ft_substr(content->content, *start, j - *start)))
			return (1);
	}
	(*current_head)->size++;
	return (0);
}

static int	handle_type_two(t_head **current_head,
	t_node *content, t_head **tab, int *i)
{
	int	j;
	int	start;

	j = 0;
	start = 0;
	while (content->content[j])
	{
		while (content->content[j] != '|' && content->content[j])
			j++;
		if (content->content[j] == '|')
		{
			if (process_pipe_segment(current_head, content, &start, j))
				return (cleant_tab_cmd(tab), 1);
			(*i)++;
			tab_new_head(tab, *i);
			if (!tab[*i])
				return (cleant_tab_cmd(tab), 1);
			*current_head = tab[*i];
			j++;
			start = j;
		}
	}
	if (process_pipe_segment(current_head, content, &start, j))
		return (cleant_tab_cmd(tab), 1);
	return (0);
}

static t_head	**initialize_split_tab(t_head *head,
		t_parse_error *error, int *size)
{
	t_head	**tab;

	*size = get_nb_head_cmds(head, error);
	if (error->error)
	{
		printf("Parse error near '%s'\n", error->target);
		return (NULL);
	}
	tab = malloc(sizeof(t_head *) * (*size + 1));
	if (!tab)
		return (NULL);
	tab[*size] = NULL;
	return (tab);
}

static int	process_list_nodes(t_head **tab,
	t_head **current_head, t_list *lst)
{
	t_node	*content;
	int		i;

	i = 0;
	while (lst)
	{
		content = lst->content;
		if (content->type != 2)
		{
			if (add_back_copy(&(*current_head)->head, lst))
				return (cleant_tab_cmd(tab), 1);
			(*current_head)->size++;
		}
		else
		{
			if (handle_type_two(current_head, content, tab, &i))
				return (1);
		}
		lst = lst->next;
	}
	return (0);
}

t_head	**split_head(t_head *head)
{
	t_parse_error	error;
	t_head			**tab;
	t_head			*current_head;
	t_list			*lst;
	int				size;

	error.error = 0;
	tab = initialize_split_tab(head, &error, &size);
	if (!tab)
		return (NULL);
	lst = head->head;
	tab_new_head(tab, 0);
	current_head = tab[0];
	if (process_list_nodes(tab, &current_head, lst))
		return (cleant_tab_cmd(tab), NULL);
	return (tab);
}
