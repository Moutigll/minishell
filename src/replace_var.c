/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:09:04 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/04 18:18:18 by tle-goff         ###   ########.fr       */
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

static int	handle_dollar_sign(t_list *curr_node, t_list *env, int i)
{
	t_env_var	*env_var;
	t_node		*node;
	char		*var_name;
	char		*before;
	char		*after;
	char		*str;

	node = (t_node *)curr_node->content;
	str = node->content;
	before = ft_substr(str, 0, i);
	var_name = extract_variable(str + i + 1);
	if (!var_name)
		return (0);
	env_var = find_env_var_node(env, var_name);
	if (str[i + 1] == '{')
		i += 2;
	i += ft_strlen(var_name);
	after = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
	free(str);
	if (before[0] == '\0')
	{
		if (env_var)
			node->content = ft_strdup(env_var->value);
		else
			node->content = ft_strdup("");
	}
	else
		node->content = before;
	if (env_var && before[0] != '\0')
	{
		node = malloc(sizeof(t_node));
		node->content = strdup(env_var->value);
		node->type = 1;
		node->head = 0;
		ft_lstinsert_after(curr_node, ft_lstnew(node));
		curr_node = curr_node->next;
	}
	else if (before[0] == '\0')
		free(before);
	if (after[0] != '\0')
	{
		node = malloc(sizeof(t_node));
		node->content = after;
		node->type = 0;
		node->head = 0;
		ft_lstinsert_after(curr_node, ft_lstnew(node));
	}
	else
		free(after);
	return (1);
}

static int	string_to_var(t_main *main, t_list *current_node)
{
	char	*str;
	char	*cpy;
	char	*error;
	int		i;

	i = 0;
	str = ((t_node *)current_node->content)->content;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\0' && str[i + 1] != '?')
		{
			if (!handle_dollar_sign(current_node, main->env->env_list, i))
				return (0);
			return (1);
		}
		else if (str[i] == '$' && str[i + 1] == '\0' && ft_strlen(str) > 1
			&& current_node->next && ((t_node *)current_node->next->content)->type != 1)
		{
			cpy = ft_strndup(str, ft_strlen(str) - 1);
			free(str);
			((t_node *)current_node->content)->content = cpy;
			if (current_node->next)
				((t_node *)current_node->next->content)->head = ((t_node *)current_node->content)->head;
		}
		else if (str[i] == '$' && str[i + 1] == '?')
		{
			error = ft_itoa(main->error);
			((t_node *)current_node->content)->content = ft_str_replace(str, "$?", error);
			str = ((t_node *)current_node->content)->content;
			free(error);
			i += ft_strlen(error) - 1;
		}
		else
			i++;
		if (str[i] == '\0' || str[i + 1] == '\0')
			break ;
	}
	return (1);
}

t_head	*replace_variables(t_head *head, t_main *main)
{
	t_list	*current_node;
	t_node	*node;

	current_node = head->head;
	while (current_node)
	{
		node = (t_node *)current_node->content;
		if (node->type != 1)
		{
			if (!string_to_var(main, current_node))
				return (free_head(head), NULL);
		}
		current_node = current_node->next;
	}
	return (head);
}
