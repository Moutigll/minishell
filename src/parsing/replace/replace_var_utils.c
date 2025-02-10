/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:29:47 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/10 18:52:56 by tle-goff         ###   ########.fr       */
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
	if (str[i] == '?' && (str[i + 1] == '\0' || str[i + 1] == '\n'
			|| (is_bracket && str[i + 1] == '}')))
		return (ft_strdup("?"));
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (is_bracket && str[i] != '}')
		return (NULL);
	return (ft_substr(str, is_bracket, i - is_bracket));
}

void	handle_content_after_var(char *after,
	t_node *node, t_list **curr_node)
{
	if (after[0] != '\0')
	{
		node = malloc(sizeof(t_node));
		node->content = after;
		node->type = 0;
		node->head = 0;
		ft_lstinsert_after(*curr_node, ft_lstnew(node));
		*curr_node = (*curr_node)->next;
	}
	else
		free(after);
}

void	handle_var_new_block(char *before,
	t_node *node, t_list **curr_node, t_env_var *env_var)
{
	if (env_var && before[0] != '\0')
	{
		node = malloc(sizeof(t_node));
		node->content = strdup(env_var->value);
		node->type = 1;
		node->head = 0;
		ft_lstinsert_after(*curr_node, ft_lstnew(node));
		*curr_node = (*curr_node)->next;
	}
	else if (before[0] == '\0')
		free(before);
}

void	handle_var_is_first(char *before,
	t_node *node, t_env_var *env_var, t_list **curr_node)
{
	char	**split;
	int		i;

	if (before[0] == '\0')
	{
		if (env_var)
		{
			i = 0;
			while (env_var->value[i] == ' ')
				i++;
			if (env_var->value && env_var->value[i] == '\0')
			{
				node->content = ft_strdup("");
				node->type = 1;
				node->head = 1;
				return ;
			}
			split = ft_split(env_var->value, ' ');
			node->content = split[0];
			node->type = 1;
			i = 1;
			if (split[i])
				node->head = 1;
			while (split[i])
			{
				node = malloc(sizeof(t_node));
				node->content = split[i];
				node->type = 1;
				node->head = 1;
				ft_lstinsert_after(*curr_node, ft_lstnew(node));
				*curr_node = (*curr_node)->next;
				i++;
			}
			if ((*curr_node)->next && ft_tablen((void **)split) > 1)
				((t_node *)(*curr_node)->next->content)->head = 1;
			free(split);
		}
		else
			node->content = ft_strdup("");
	}
	else
		node->content = before;
}
