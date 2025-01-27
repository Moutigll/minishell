/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:10:25 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/24 17:09:44 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_head	*return_head(t_head *head, int i)
{
	t_head	*new_head;
	t_list	*lst;

	lst = return_lst(head, i);
	new_head = malloc(sizeof(t_head));
	new_head->head = lst;
	new_head->size = head->size;
	return (new_head);
}

t_list	*return_lst(t_head *head, int i)
{
	t_list	*lst;
	int		n;

	n = 0;
	lst = head->head;
	while (lst && i > n)
	{
		if (!lst->next)
			break ;
		lst = lst->next;
		n++;
	}
	return (lst);
}

int	find_block(t_head *head, int *n, char **content_block, int boolean)
{
	t_node	*node;
	t_list	*lst;
	int		i;

	i = 0;
	if (!head->head)
		return (*n = -1, -1);
	*content_block = "\0";
	lst = head->head;
	while (lst)
	{
		i++;
		node = lst->content;
		if (i - 1 != 0 && node->head == 1)
			return (i);
		if (boolean == 1)
			*content_block = ft_strjoin((const char *)*content_block,
					(const char *)node->content);
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (*n = -1, -1);
}

static int	count_tab(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int is_node_visited(t_list *visited, t_list *node)
{
	while (visited)
	{
		if (visited->content == node->content)
			return (1);
		visited = visited->next;
	}
	return (0);
}

t_list *find_min_node(t_list *lst, t_list *visited)
{
	t_list		*min_node = NULL;
	t_env_var	*tmp;
	t_env_var	*tmp_2;

	while (lst)
	{
		if (!is_node_visited(visited, lst))
		{
			tmp = lst->content;
			if (min_node != NULL)
				tmp_2 = min_node->content;
			if (!min_node || strcmp(tmp->name, tmp_2->name) < 0)
				min_node = lst;
		}
		lst = lst->next;
	}
	return (min_node);
}

void print_ascii_sorted(t_list *lst)
{
	t_list		*min_node;
	t_list		*current;
	t_list		*visited;
	t_env_var	*tmp;

	visited = NULL;
	while ((min_node = find_min_node(lst, visited)) != NULL)
	{
		tmp = min_node->content;
		if (((int)ft_strlen(tmp->name) != 1 || tmp->name[0] != '_') && tmp->exported == 1)
			printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
		else if (((int)ft_strlen(tmp->name) != 1 || tmp->name[0] != '_') && tmp->exported == 0)
			printf("declare -x %s\n", tmp->name);
		current = malloc(sizeof(t_list));
		if (!current)
		{
			fprintf(stderr, "Error: malloc failed\n");
			ft_lstclear(&visited, free);
			return ;
		}
		current->content = min_node->content;
		current->next = visited;
		visited = current;
	}
}

int	export_cmd(t_list *lst/*, char **args */)
{
	char	*args[] = {"export", "oui=non", "5oui=", NULL};
	int		i;

	i = 1;
	if (ft_strcmp(args[0], "export") == 0)
	{
		if (count_tab(args) == 1)
			print_ascii_sorted(lst);
		while (args[i])
		{
			check_type_export(args[i], lst);
			i++;
		}
	}
	print_ascii_sorted(lst);
	g_status = 0;
	// update here
	return (0);
}
