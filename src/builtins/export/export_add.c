/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:49:31 by tle-goff          #+#    #+#             */
/*   Updated: 2025/02/10 21:32:28 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	add_key(char **key, char *str)
{
	*key = return_key(str);
	if (key == NULL)
		return (MALLOC_ERROR);
	return (0);
}

static int	add_node(t_envirronement *var, char *str, int count, int i)
{
	int			index;
	char		*tmp;
	char		*key;

	if (add_key(&key, str) != 0)
		return (MALLOC_ERROR);
	index = check_exist(var->env_list, key);
	if (str[ft_strlen(key)] != '\0')
	{
		tmp = return_value(str);
		if (!tmp)
			return (free(key), MALLOC_ERROR);
	}
	else
		tmp = ft_strdup("");
	if (index >= 0)
		return (change_var(tmp, index, var->env_list),
			change_pwd(var->env_list, var->envp), free(key), free(tmp), 0);
	else if ((count == 1 && str[i - 1] != '=') || count > 1)
		return (add_var(var->env_list, new_var_node(key, tmp, 1)), 0);
	else if (count == 1 && str[i - 1] == '=')
		add_var(var->env_list, new_var_node(key, ft_strdup(""), 1));
	else
		add_var(var->env_list, new_var_node(key, ft_strdup(""), 0));
	return (free(tmp), 0);
}

void	print_indentifier(char *part1, char *str)
{
	ft_putstr_fd(part1, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	check_type_export(char *str, t_envirronement *var)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (count == 0 && (str[i] == '-' || str[i] == '+'
				|| str[i] == '.' || str[i] == '{' || str[i] == '}'
				|| str[i] == '*' || str[i] == '#' || str[i] == '@'
				|| str[i] == '!' || str[i] == '~' || str[i] == '^'))
		{
			print_indentifier("minicoquille: export: `", str);
			return (1);
		}
		if (str[i++] == '=')
			count++;
	}
	if ((!ft_isalpha(str[0]) && str[0] != '_') || check_quote_key(str) == 1)
	{
		print_indentifier("export: `", str);
		return (1);
	}
	return (add_node(var, str, count, i));
}
