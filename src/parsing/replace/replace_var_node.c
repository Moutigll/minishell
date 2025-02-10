/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:20:12 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/10 19:37:50 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	remove_empty_var(char *str, t_list *current_node)
{
	char	*cpy;

	cpy = ft_strndup(str, ft_strlen(str) - 1);
	free(str);
	((t_node *)current_node->content)->content = cpy;
	if (current_node->next)
		((t_node *)current_node->next->content)->head = \
		((t_node *)current_node->content)->head;
}

static int	prep_replace_var(t_env_var *env_var,
	int *i, char ***split, t_node *node)
{
	while (env_var->value[*i] == ' ')
		(*i)++;
	if (env_var->value && env_var->value[*i] == '\0')
	{
		node->content = ft_strdup("");
		node->type = 1;
		node->head = 1;
		return (1);
	}
	(*split) = ft_split(env_var->value, ' ');
	node->content = (*split)[0];
	node->type = 1;
	(*i) = 1;
	if ((*split)[1])
		node->head = 1;
	return (0);
}

static void	create_new_var_nodes(char **split,
	t_list **curr_node, t_node *node, int i)
{
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
			if (prep_replace_var(env_var, &i, &split, node))
				return ;
			create_new_var_nodes(split, curr_node, node, i);
		}
		else
			node->content = ft_strdup("");
	}
	else
		node->content = before;
}
