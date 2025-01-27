/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:49:31 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/27 20:25:38 by tle-goff         ###   ########.fr       */
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
			var->value = value;
			var->exported = 1;
			break ;
		}
		if (!lst->next)
			break ;
		lst = lst->next;
		i++;
	}
}

static t_list	*new_var_node(char *str, char *key, char *value, int n)
{
	t_env_var	*node;
	t_list		*lst;

	node = new_var(str, key, value, 1);
	if (!node)
		return (g_status = MALLOC_ERROR, free(key), free(value), NULL);
	lst = ft_lstnew(node);
	if (!lst)
		return (g_status = MALLOC_ERROR, free(node), NULL);
	return (lst);
}

static int	add_node(t_list *lst, char *str, int count, int i)
{
	char		*value;
	int			index;
	char		*tmp;
	char		*key;

	key = return_key(str);
	if (key == NULL)
		return (g_status = MALLOC_ERROR, 0);
	index = check_exist(lst, key);
	tmp = return_value(str);
	if (!tmp)
		return (g_status = MALLOC_ERROR, free(key), 0);
	if (index >= 0)
		change_var(tmp, index, lst);
	else if ((count == 1 && str[i - 1] != '=') || count > 1)
		ft_lstadd_back(&lst, new_var_node(str, key, tmp, 1));
	else if (count == 1 && str[i - 1] == '=')
		ft_lstadd_back(&lst, new_var_node(str, key, ft_strdup(""), 1));
	else
		ft_lstadd_back(&lst, new_var_node(str, key, ft_strdup(""), 0));
	return (0);
}

void	check_type_export(char *str, t_list *lst)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (str[i])
		if (str[i++] == '=')
			count++;
	if (check_first_char(str[0]) == 0)
	{
		printf("`%s' not a valid identifier\n", str);
		return ;
	}
	add_node(lst, str, count, i);
}
