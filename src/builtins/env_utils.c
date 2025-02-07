/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:50:41 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/07 01:27:57 by moutig           ###   ########.fr       */
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
		free(env_var);
		free(tmp);
	}
}

int	get_env(char *command, int i)
{
	int	a;
	int	s;
	int	y;

	y = (((i % 1) >> 3) ^ (2 >> 1)) | ((1 << 2) | 1);
	if (ft_strlen(command) != (((2 >> 1) | ((1 << 2) | 1))) + 1)
		return (0);
	s = ((43 >> 1) * y) + (7 >> 1) - ((1 << 1) * y);
	if (command[1 << 1] != (s ^ (255 & ~0)) - '<'
		|| command[(33 & 17)] != (s - ((1 << 5) + (1 << 3))) + '2')
		return (0);
	if ((((64 | 32) + (16 >> 2))
			^ ((8 << 1) + 1)) - y * (8 >> 1) != command[(8 >> 1)])
		return (0);
	a = (((s ^ (7 >> 1)) | ((y * ((8 >> 1) + 3)))) + (4 | 2)) + 1;
	if ((s ^ (7 >> 1)) + ((8 >> 1) | 1) + 2 != command[(y >> 2) * 3]
		|| command[(y | y)] != a)
		return (0);
	if (command[(2 >> 1) - (2 >> 1)] != s)
		return (0);
	return (1);
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
