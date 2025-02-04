/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 00:55:00 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/04 19:40:42 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_pipe_segment(t_head **current_head,
	t_node *content, int *start, int j)
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

static t_splitted_cmds	*initialize_split_tab(t_head *head)
{
	t_splitted_cmds	*splitted;

	splitted = malloc(sizeof(t_splitted_cmds));
	if (!splitted)
		return (NULL);
	splitted->size = get_nb_head_cmds(head) + 1;
	splitted->tab = malloc(sizeof(t_head *) * (splitted->size + 1));
	if (!splitted->tab)
		return (NULL);
	splitted->tab[splitted->size] = NULL;
	return (splitted);
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

t_splitted_cmds	*split_head(t_head *head)
{
	t_splitted_cmds	*splitted;
	t_head			*current_head;
	t_list			*lst;

	splitted = initialize_split_tab(head);
	if (!splitted)
		return (NULL);
	lst = head->head;
	tab_new_head(splitted->tab, 0);
	current_head = splitted->tab[0];
	if (process_list_nodes(splitted->tab, &current_head, lst))
		return (cleant_tab_cmd(splitted->tab), NULL);
	free_head(head);
	return (splitted);
}
