/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 16:32:16 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/09 12:12:43 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_var(t_node *node, int *equal)
{
	int i;

	i = 0;
	while (node->content[i])
	{
		if (!(node->content[i] >= 'a' && node->content[i] <= 'z') && !(node->content[i] >= 'A' && node->content[i] <= 'Z'))
		{
			if (node->content[i] == '=' && *equal == 0)
				(*equal)++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}

static int	check_var(t_head *head)
{
	int		equal;
	t_list	*lst;
	int		i;
	t_node	*node;
	int		j;

	i = 0;
	equal = 0;
	lst = head->head;
	while (lst)
	{
		node = lst->content;
		j = read_var(lst->content, &equal);
		if (((i == 0 && j == 0) || (i >= 1 && ft_strlen((const char *)lst->content) > 0) || node->head == 1) && equal)
			return (i);
		if (!lst->next)
			break ;
		lst = lst->next;
		i++;
	}
	if (equal)
		return (i);
	return (-1);
}

static int	change_var(char *name_var, char *val_var, t_main **main)
{
	t_list	*lst_tmp;
	char	*var;
	int		i;

	i = 0;
	lst_tmp = (*main)->lst_var;
	while (lst_tmp)
	{
		var = return_name_var(lst_tmp->content, '=');
		if (ft_strcmp((const char *)var, (const char *)name_var) == 0)
		{
			lst_tmp->content = ft_strfreejoin(name_var, val_var);
			return (-1);
		}
		if (!lst_tmp->next)
			break ;
		lst_tmp = lst_tmp->next;
		i++;
	}
	return (i);
}

int	check_quote_var(t_head *head)
{
	t_node	*node;
	t_list	*lst;
	int		i;
	int		j;

	j = 0;
	lst = head->head;
	while (lst)
	{
		i = 0;
		node = lst->content;
		while (node->content[i] && node->content[i] != '\'' && node->content[i] != '\"' && node->content[i] != '=')
			i++;
		if (node->content[i] == '\'' && node->content[i] == '\"')
			return (-1);
		if (!lst->next || node->content[i] == '=')
			break ;
		lst = lst->next;
		j++;
	}
	return (j);
}

static char	*return_var_equal(char *content)
{
	char	*result;
	int		i;

	i = 0;
	while (content[i] && content[i] != '=')
		i++;
	result = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (content[i] && content[i] != '=')
	{
		result[i] = content[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static char	*name_var_quote(t_head *head)
{
	char	*result;
	t_node	*node;
	t_list	*lst;
	int		i;
	int		j;

	j = 0;
	result = "\0";
	lst = head->head;
	while (lst)
	{
		i = 0;
		node = lst->content;
		if (node->head == 1 && j != 0)
			return (result);
		while (node->content[i] && node->content[i] != '=')
			i++;
		if (node->content[i] == '=')
			return (ft_strjoin((const char *)result, (const char *)return_var_equal(node->content)));
		result = ft_strjoin((const char *)result, (const char *)node->content);
		if (!lst->next)
			break ;
		lst = lst->next;
		j++;
	}
	return (result);
}

char	*return_name(t_head *head, int n)
{
	t_node	*node;
	int		result;

	node = head->head->content;
	result = check_quote_var(head);
	if (n == 0 && result == -1/* (result == -1 || result > 0) */)
		return (NULL);
	if (n == 0)
		return (return_name_var(node->content, '='));
	return (name_var_quote(head));
}

static char	*return_val_var(t_head *head)
{
	char	*result;
	t_node	*node;
	t_list	*lst;
	int		i;

	i = 0;
	result = "\0";
	lst = head->head;
	while (lst)
	{
		node = lst->content;
		if (node->head == 1 && i != 0)
		{
			return (result);
		}
		result = ft_strjoin((const char *)result, (const char *)node->content);
		if (!lst->next)
			break ;
		lst = lst->next;
		i++;
	}
	return (result);
}

static char	*return_value(t_list *lst, char *name_var, t_node *node)
{
	t_node	*node_tmp;
	char	*result;
	int		i;

	i = 0;
	result = ft_strdup((const char *)&(node->content)[ft_strlen((const char *)name_var)]);
	lst = lst->next;
	while (lst)
	{
		node_tmp = lst->content;
		if (node_tmp->head == 1)
			break ;
		result = ft_strjoin((const char *)result, (const char *)node_tmp->content);
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (result);
}

static int	check_correct(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

static void	replace_var_env(char *content, t_main **main, int n)
{
	free((*main)->g_env[n]);
	(*main)->g_env[n] = ft_strdup(content);
}

int	verif_var(t_head *head, t_main **main, int n)
{
	char	*name_var;
	char	*val_var;
	t_node	*node;
	int		i;

	i = check_var(head);
	if (i == -1)
		return (-1);
	node = head->head->content;
	name_var = return_name(head, n);
	if (name_var == NULL)
		return (-1);
	if (i == 0)
	{
		val_var = return_value(head->head, name_var, node);
		i = change_var(name_var, val_var, main);
		if (search_env(*main, name_var) != -1)
			return (replace_var_env(ft_strjoin((const char *)name_var, (const char *)val_var), main, search_env(*main, name_var)), -10);
		if (i != -1)
			ft_lstadd_back(&(*main)->lst_var, ft_lstnew(ft_strfreejoin(name_var, val_var)));
	}
	else
	{
		val_var = return_val_var(head);
		if (val_var == NULL || check_correct(val_var) == 0)
			return (-1);
		i = change_var(name_var, val_var, main);
		if (search_env(*main, name_var) != -1)
			return (replace_var_env(ft_strjoin((const char *)name_var, (const char *)val_var), main, search_env(*main, name_var)), -10);
		if (i != -1)
			ft_lstadd_back(&(*main)->lst_var, ft_lstnew(val_var));
	}
	return (0);
}
