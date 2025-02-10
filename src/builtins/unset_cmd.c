/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:51:16 by tle-goff          #+#    #+#             */
/*   Updated: 2025/02/10 18:51:46 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	free_unset(t_env_var *var, t_list *current)
{
	free(var->name);
	free(var->value);
	free(current->content);
	free(current);
}

static void	remove_node(t_list **head, char *key)
{
	t_list		*current;
	t_list		*prev;
	t_env_var	*var;

	if (!head || !*head)
		return ;
	current = *head;
	prev = NULL;
	while (current)
	{
		var = current->content;
		if (ft_strcmp(var->name, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			free_unset(var, current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

static int	check_contain(t_list *lst, char *key)
{
	t_env_var	*node;

	while (lst)
	{
		node = lst->content;
		if (ft_strcmp(node->name, key) == 0)
			return (1);
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (0);
}

int	unset_cmd(t_list *lst, char **args, t_main *main)
{
	int	i;

	i = 1;
	if (ft_strcmp(args[0], "unset") == 0)
	{
		while (args[i])
		{
			if (check_contain(lst, args[i]) == 1)
				remove_node(&lst, args[i]);
			i++;
		}
	}
	main->error = 0;
	update_env(main->env);
	return (0);
}
