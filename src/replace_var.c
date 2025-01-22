/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:09:04 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/23 00:10:45 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_env_var	*find_env_var_node(t_list *env, const char *var_name)
{
	t_env_var	*env_var;

	while (env)
	{
		env_var = (t_env_var *)env->content;
		if (strcmp(env_var->name, var_name) == 0)
			return (env_var);
		env = env->next;
	}
	return (NULL);
}

static char	*extract_variable(char *str)
{
	int	is_bracket;
	int	i;

	if (str[0] == '{')
	{
		is_bracket = 1;
		i = 1;
	}
	else
	{
		is_bracket = 0;
		i = 0;
	}
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (is_bracket && str[i] != '}')
		return (NULL);
	return (ft_substr(str, is_bracket, i - is_bracket));
}

static char	*handle_dollar_sign(char *str, int *i, t_list *env)
{
	t_env_var	*env_var;
	char		*variable;
	char		*full_variable;
	char		*tmp;

	variable = extract_variable(&str[*i + 1]);
	if (!variable)
		return (NULL);
	env_var = find_env_var_node(env, variable);
	if (str[*i + 1] == '{')
		*i += 2;
	*i += ft_strlen(variable);
	full_variable = ft_strjoin("$", variable);
	if (str[*i] == '}')
	{
		full_variable = ft_strjoin("${", variable);
		full_variable = ft_strjoin(full_variable, "}");
		(*i)++;
	}
	tmp = str;
	if (env_var)
		str = ft_str_replace(str, full_variable, env_var->value);
	else
		str = ft_str_replace(str, full_variable, "");
	return (free(tmp), free(variable), free(full_variable), str);
}

static char	*string_to_var(char *str, t_list *env)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\0')
		{
			str = handle_dollar_sign(str, &i, env);
			if (!str)
				return (NULL);
		}
		else
			i++;
	}
	return (str);
}

t_head	*replace_variables(t_head *head, t_envirronement *env)
{
	t_list	*current_node;

	current_node = head->head;
	while (current_node)
	{
		if (((t_node *)current_node->content)->type == 0
			|| ((t_node *)current_node->content)->type == 2)
		{
			((t_node *)current_node->content)->content = string_to_var(
					((t_node *)current_node->content)->content, env->env_list);
			if (!((t_node *)current_node->content)->content)
				return (NULL);
		}
		current_node = current_node->next;
	}
	return (head);
}
