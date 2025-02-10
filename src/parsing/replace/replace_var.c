/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:09:04 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/10 19:47:57 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_dollar_sign_char(char c)
{
	if (c != '\0' && c != '\n' && c != ' ' && c != '$' && c != '\'' && c != '/'
		&& c != '.')
		return (1);
	return (0);
}

static int	handle_dollar_sign(t_list *curr_node, t_list *env, int i)
{
	t_env_var	*env_var;
	t_node		*node;
	char		*var_name;
	char		*before;
	char		*after;

	node = (t_node *)curr_node->content;
	before = ft_substr(node->content, 0, i);
	var_name = extract_variable(node->content + i + 1);
	if (node->content[i + 1] == '{')
		i += 2;
	i += ft_strlen(var_name);
	after = ft_substr(node->content, i + 1, ft_strlen(node->content) - i - 1);
	if (handle_dollar_sign_char(node->content[i + 1]))
		env_var = NULL;
	else
		env_var = find_env_var_node(env, var_name);
	free(node->content);
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

static int	string_to_var(t_main *main, t_list *curr_nd)
{
	char	*str;
	int		i;

	i = 0;
	str = ((t_node *)curr_nd->content)->content;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\0'
			&& str[i + 1] != ' ' && str[i + 1] != '?')
		{
			if (!handle_dollar_sign(curr_nd, main->env->env_list, i))
				return (0);
			return (1);
		}
		else if (str[i] == '$' && str[i + 1] == '\0' && ft_strlen(str) > 1
			&& curr_nd->next && ((t_node *)curr_nd->next->content)->type != 1)
			remove_empty_var(str, curr_nd);
		else if (str[i] == '$' && str[i + 1] == '?')
			replace_error_code(&str, main, curr_nd, &i);
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
