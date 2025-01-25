/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:53:45 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/25 13:12:01 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_node_content(t_node *content, t_parse_error *error)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (content->content[j])
	{
		while (content->content[j] && content->content[j] != '|')
			j++;
		if (content->content[j] && content->content[j] == '|')
		{
			count++;
			j++;
		}
	}
	return (count);
}

int	get_nb_head_cmds(t_head *head, t_parse_error *error)
{
	t_list	*lst;
	t_node	*content;
	int		i;

	i = 0;
	lst = head->head;
	while (lst)
	{
		content = lst->content;
		if (content->type == 2)
		{
			if (!check_node_content(content, error))
				return (0);
			i++;
		}
		lst = lst->next;
	}
	return (i);
}

int	tab_new_head(t_head **tab, int i)
{
	tab[i] = malloc(sizeof(t_head));
	if (!tab[i])
		return (1);
	tab[i]->head = NULL;
	tab[i]->size = 0;
	return (0);
}

int	add_back_copy(t_list **head, t_list *lst)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (1);
	new->content = malloc(sizeof(t_node));
	if (!new->content)
		return (1);
	((t_node *)new->content)->content = ft_strdup(
			((t_node *)lst->content)->content);
	if (!((t_node *)new->content)->content)
		return (1);
	((t_node *)new->content)->type = ((t_node *)lst->content)->type;
	((t_node *)new->content)->head = ((t_node *)lst->content)->head;
	new->next = NULL;
	ft_lstadd_back(head, new);
	return (0);
}

int	add_before_pipe(t_list **head, int ishead, char *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (1);
	new->content = malloc(sizeof(t_node));
	if (!new->content)
		return (1);
	((t_node *)new->content)->content = content;
	if (!((t_node *)new->content)->content)
		return (1);
	((t_node *)new->content)->type = 2;
	((t_node *)new->content)->head = ishead;
	new->next = NULL;
	ft_lstadd_back(head, new);
	return (0);
}
