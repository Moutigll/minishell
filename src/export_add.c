/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:49:31 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/24 17:00:38 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_first_char(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

static char	*return_value(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] != '\0')
		return (ft_strdup(&str[i + 1]));
	return (NULL);
}

static char	*return_key(char *str)
{
	char	*result;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	result = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] && str[i] != '=')
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static t_env_var	*new_var(char *str, char *key, char *value, int exported)
{
	t_env_var	*tmp;

	tmp = malloc(sizeof(t_env_var *));
	tmp->exported = exported;
	tmp->name = key;
	tmp->value = value;
	return (tmp);
}

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

void	check_type_export(char *str, t_list *lst)
{
	int		index;
	int		count;
	char	*key;
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
	key = return_key(str);
	index = check_exist(lst, key);
	if (index >= 0)
		change_var(return_value(str), index, lst);
	else if ((count == 1 && str[i - 1] != '=') || count > 1)
		ft_lstadd_back(&lst, ft_lstnew(new_var(str, key, return_value(str), 1)));
	else if (count == 1 && str[i - 1] == '=')
		ft_lstadd_back(&lst, ft_lstnew(new_var(str, key, ft_strdup(""), 1)));
	else
		ft_lstadd_back(&lst, ft_lstnew(new_var(str, key, ft_strdup(""), 0)));
}
