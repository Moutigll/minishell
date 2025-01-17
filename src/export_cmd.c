/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:10:25 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/20 15:30:53 by tle-goff         ###   ########.fr       */
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

static char	*search_lst_var(t_list *lst, char *key)
{
	while (lst)
	{
		if (ft_strcmp((const char *)return_before(lst->content),
				(const char *)key) == 0)
			return (lst->content);
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (NULL);
}

static void	remove_last_element(t_list **lst)
{
	t_list	*current;
	t_list	*prev;

	if (!lst || !*lst)
		return ;
	current = *lst;
	if (!current->next)
	{
		free(current->content);
		free(current);
		*lst = NULL;
		return ;
	}
	while (current->next)
	{
		prev = current;
		current = current->next;
	}
	free(current);
	prev->next = NULL;
}

static t_list	*remove_node_by_content_part1(t_list **prev,
		t_list **current, t_list **next_node, t_list *lst)
{
	*next_node = (*current)->next;
	free((*current)->content);
	free(*current);
	if (*prev == NULL)
		return (*next_node);
	else
	{
		(*prev)->next = *next_node;
		return (lst);
	}
}

static t_list	*remove_node_by_content(t_list *lst, char *str)
{
	t_list	*current;
	t_list	*prev;
	t_list	*next_node;

	if (!lst || !str)
		return (lst);
	current = lst;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp((const char *)current->content, (const char *)str) == 0)
		{
			lst = remove_node_by_content_part1(&prev,
					&current, &next_node, lst);
			current = next_node;
			continue ;
		}
		prev = current;
		current = current->next;
	}
	return (lst);
}

static int	export_cmd_part(t_head *head, t_main *main)
{
	char	*attach;

	attach = attach_block(head);
	if (ft_strncmp(attach, "export", 6) == 0)
	{
		env_cmd_direct(main);
		free(attach);
		return (1);
	}
	free(attach);
	return (0);
}

static void	export_cmd_part2(t_main **main, char *tmp, char *content_tmp)
{
	if (search_env(*main, return_before(tmp)) == -1)
		(*main)->g_env = ft_realoc_ptr((*main)->g_env, content_tmp);
	else
	{
		free((*main)->g_env[search_env(*main, return_before(tmp))]);
		(*main)->g_env[search_env(*main,
				return_before(tmp))] = ft_strdup(content_tmp);
	}
}

static void	export_cmd_part1(t_head *node, t_main **main, char **content_tmp)
{
	int		result;
	char	*tmp;

	result = verif_var(node, main, 1);
	if (result == 0)
	{
		remove_last_element(&(*main)->lst_var);
		tmp = return_before(*content_tmp);
		export_cmd_part2(main, tmp, *content_tmp);
		free(tmp);
	}
	else if (result != -10)
	{
		if (search_env(*main, *content_tmp) == -1)
		{
			(*main)->g_env = ft_realoc_ptr((*main)->g_env,
					search_lst_var((*main)->lst_var, *content_tmp));
			(*main)->lst_var = remove_node_by_content((*main)->lst_var,
					search_lst_var((*main)->lst_var, *content_tmp));
		}
	}
	if (*content_tmp != NULL)
		free(*content_tmp);
}

int	export_cmd(t_head *head, t_main **main)
{
	t_head	*node;
	char	*content_tmp;
	int		tmp;
	int		n;
	int		i;

	tmp = check_equal("export", head, 0);
	n = tmp;
	i = n;
	if (tmp >= 0)
	{
		tmp = 0;
		while (n != -1)
		{
			node = return_head(head, i);
			find_block(node, &n, &content_tmp, 1);
			export_cmd_part1(node, main, &content_tmp);
			i += find_block(node, &n, &content_tmp, 0) - 1;
			free(node);
			tmp++;
		}
		return (1);
	}
	else
		return (export_cmd_part(head, *main));
}
