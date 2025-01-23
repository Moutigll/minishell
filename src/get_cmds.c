/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 00:55:00 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/23 01:56:21 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_nb_head_cmds(t_head *head, t_parse_error *error)
{
	t_list	*lst;
	t_node	*content;
	int		i;
	int		j;

	i = 0;
	lst = head->head;
	while (lst)
	{
		content = lst->content;
		if (content->type == 2)
		{
			j = 0;
			while (content->content[j])
			{
				while (content->content[j] && content->content[j] == ' ')
					j++;
				if (content->content[j] && content->content[j] == '|'
					&& content->content[j + 1] == '|')
					return (error->error = 1, error->target = content->content, 0);
				if (content->content[j] && content->content[j] == '|')
				{
					i++;
					j++;
				}
				while (content->content[j] && content->content[j]  == ' ')
					j++;
				j++;
			}
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
	((t_node *)new->content)->content = ft_strdup(((t_node *)lst->content)->content);
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

t_head **split_head(t_head *head)
{
	t_parse_error error = {0, NULL};
	t_head **tab;
	t_head *current_head;
	t_list *lst;
	t_node *content;
	int size, i = 0;

	size = get_nb_head_cmds(head, &error);
	if (error.error)
		return (printf("Parse error near '%s'\n", error.target), NULL);

	tab = malloc(sizeof(t_head *) * (size + 1));
	if (!tab)
		return (NULL);
	tab[size] = NULL;

	lst = head->head;
	tab_new_head(tab, i);
	current_head = tab[i];
	while (lst)
	{
		content = lst->content;
		if (content->type != 2)
		{
			if (add_back_copy(&current_head->head, lst))
				return (free_tab((void **)tab), NULL);
			current_head->size++;
		}
		else
		{
			int j = 0, start = 0;
			while (content->content[j])
			{
				while (content->content[j] != '|' && content->content[j])
					j++;
				if (content->content[j] == '|')
				{
					if (add_before_pipe(&current_head->head, content->head, ft_substr(content->content, start, j - start)))
						return (free_tab((void **)tab), NULL);
					current_head->size++;
					i++;
					tab_new_head(tab, i);
					current_head = tab[i];
					j++;
					start = j;
				}
			}
			if (add_before_pipe(&current_head->head, content->head, ft_substr(content->content, start, j - start)))
				return (free_tab((void **)tab), NULL);
			current_head->size++;
		}
		lst = lst->next;
	}
	i = 0;
	while (i < size)
	{
		printf("\n\n\nHEAD NUMBER %d:\n", i);
		print_head(tab[i]->head);
		i++;
	}
	return (tab);
}
