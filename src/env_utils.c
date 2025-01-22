/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:50:41 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/22 19:57:39 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_env(t_list *env)
{
	t_list		*tmp;
	t_env_var	*env_var;

	while (env)
	{
		tmp = env;
		env = env->next;
		env_var = tmp->content;
		free(env_var->name);
		free(env_var->value);
		free(tmp);
	}
}

static int	fill_env_node(t_list *node, char *env)
{
	t_env_var	*env_var;
	char		*delimiter;

	env_var = malloc(sizeof(t_env_var));
	if (!env_var)
		return (0);
	delimiter = ft_strchr(env, '=');
	if (delimiter)
	{
		env_var->name = ft_substr(env, 0, delimiter - env);
		env_var->value = ft_strdup(delimiter + 1);
	}
	else
	{
		env_var->name = ft_strdup(env);
		env_var->value = NULL;
	}
	if (!env_var->name || (delimiter && !env_var->value))
		return (free(env_var->name),
			free(env_var->value),
			free(env_var), 0);
	node->content = env_var;
	return (1);
}

t_list	*create_env_list(char **env)
{
	t_list	*lst;
	t_list	*new_node;
	int		i;

	lst = NULL;
	i = 0;
	while (env[i])
	{
		new_node = malloc(sizeof(t_list));
		if (!new_node)
			return (free_env(lst), NULL);
		if (!fill_env_node(new_node, env[i]))
		{
			free(new_node);
			return (free_env(lst), NULL);
		}
		((t_env_var *)new_node->content)->exported = 1;
		new_node->next = NULL;
		ft_lstadd_back(&lst, new_node);
		i++;
	}
	return (lst);
}

//DEBUG

void	print_env(t_list *env)
{
	t_list		*tmp;
	t_env_var	*env_var;

	tmp = env;
	printf("Printing env:\n");
	while (tmp)
	{
		env_var = tmp->content;
		printf("name: %s\n", env_var->name);
		printf("value: %s\n", env_var->value);
		printf("exported: %d\n", env_var->exported);
		tmp = tmp->next;
	}
}
