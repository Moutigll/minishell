/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:49:31 by tle-goff          #+#    #+#             */
/*   Updated: 2025/02/05 19:41:14 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_exist(t_list *lst, char *str)
{
	t_env_var	*var;
	int			i;

	i = 0;
	while (lst)
	{
		var = lst->content;
		if (ft_strcmp(var->name, str) == 0)
			return (i);
		if (!lst->next)
			break ;
		lst = lst->next;
		i++;
	}
	return (-1);
}

static void	change_var(char *value, int index, t_list *lst)
{
	t_env_var	*var;
	int			i;

	i = 0;
	if (value == NULL)
		return ;
	while (lst)
	{
		var = lst->content;
		if (i == index)
		{
			free(var->value);
			var->value = ft_strdup(value);
			var->exported = 1;
			break ;
		}
		if (!lst->next)
			break ;
		lst = lst->next;
		i++;
	}
}

static t_list	*new_var_node(char *key, char *value, int n)
{
	t_env_var	*node;
	t_list		*lst;

	if (!value)
		return (NULL);
	node = new_var(key, value, n);
	if (!node)
		return (free(key), free(value), NULL);
	lst = ft_lstnew(node);
	if (!lst)
		return (free(node), NULL);
	return (lst);
}

static int	add_node(t_list *lst, char *str, int count, int i)
{
	int			index;
	char		*tmp;
	char		*key;

	key = return_key(str);
	if (key == NULL)
		return (MALLOC_ERROR);
	index = check_exist(lst, key);
	tmp = return_value(str);
	if (!tmp)
		return (free(key), MALLOC_ERROR);
	if (index >= 0)
		return (change_var(tmp, index, lst), free(key), free(tmp), 0);
	else if ((count == 1 && str[i - 1] != '=') || count > 1)
		return (add_var(lst, new_var_node(key, tmp, 1)), 0);
	else if (count == 1 && str[i - 1] == '=')
		add_var(lst, new_var_node(key, ft_strdup(""), 1));
	else
		add_var(lst, new_var_node(key, ft_strdup(""), 0));
	free(tmp);
	return (0);
}

int	check_type_export(char *str, t_list *lst)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (str[i])
		if (str[i++] == '=')
			count++;
	if (check_first_char(str[0]) == 0 || check_quote_key(str) == 1)
	{
		printf("`%s' not a valid identifier\n", str);
		return (1);
	}
	return (add_node(lst, str, count, i));
}
