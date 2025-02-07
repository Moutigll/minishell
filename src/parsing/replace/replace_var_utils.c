/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:29:47 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/07 01:08:32 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_var	*find_env_var_node(t_list *env, const char *var_name)
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

char	*extract_variable(char *str)
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

void	handle_content_after_var(char *after,
	t_node *node, t_list *curr_node)
{
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
}

void	handle_var_new_block(char *before,
	t_node *node, t_list *curr_node, t_env_var *env_var)
{
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
}

void	handle_var_is_first(char *before,
	t_node *node, t_env_var *env_var)
{
	if (before[0] == '\0')
	{
		if (env_var)
		{
			node->content = ft_strdup(env_var->value);
			node->type = 1;
		}
		else
			node->content = ft_strdup("");
	}
	else
		node->content = before;
}
