/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:09:04 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/09 17:40:39 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	if (str[i + 1] == '{')
		i += 2;
	i += ft_strlen(var_name);
	if (str[i + 1] != '\0' && str[i + 1] != '\n' && str[i + 1] != ' ' && str[i + 1] != '$' && str[i + 1] != '\'' && str[i + 1] != '/')
		env_var = NULL;
	else
		env_var = find_env_var_node(env, var_name);
	after = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
	free(str);
	handle_var_is_first(before, node, env_var, &curr_node);
	handle_var_new_block(before, node, &curr_node, env_var);
	handle_content_after_var(after, node, &curr_node);
	return (free(var_name), 1);
}

static void	replace_error_code(char **str,
	t_main *main, t_list *current_node, int *i)
{
	char	*error;

	error = ft_itoa(main->error);
	*str = ft_str_replace(*str, "$?", error);
	free(((t_node *)current_node->content)->content);
	((t_node *)current_node->content)->content = *str;
	*i += ft_strlen(error) - 1;
	free(error);
}

static void	remove_empty_var(char *str, t_list *current_node)
{
	char	*cpy;

	cpy = ft_strndup(str, ft_strlen(str) - 1);
	free(str);
	((t_node *)current_node->content)->content = cpy;
	if (current_node->next)
		((t_node *)current_node->next->content)->head = \
		((t_node *)current_node->content)->head;
}

static int	string_to_var(t_main *main, t_list *current_node)
{
	char	*str;
	int		i;

	i = 0;
	str = ((t_node *)current_node->content)->content;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\0' && str[i + 1] != ' ' && str[i + 1] != '?')
		{
			if (!handle_dollar_sign(current_node, main->env->env_list, i))
				return (0);
			return (1);
		}
		else if (str[i] == '$' && str[i + 1] == '\0' && ft_strlen(str) > 1
			&& current_node->next
			&& ((t_node *)current_node->next->content)->type != 1)
			remove_empty_var(str, current_node);
		else if (str[i] == '$' && str[i + 1] == '?')
			replace_error_code(&str, main, current_node, &i);
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
