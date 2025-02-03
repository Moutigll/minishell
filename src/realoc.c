/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:15:31 by tle-goff          #+#    #+#             */
/*   Updated: 2025/02/03 13:41:14 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_ptr(t_envirronement *env, char *key, char *value)
{
	char	*result;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (-1);
	result = ft_strjoin(tmp, value);
	free(tmp);
	if (!result)
		return (-1);
	while (env->envp[i])
	{
		if (ft_strcmp(env->envp[i], result) == 0)
			return (free(result), 1);
		i++;
	}
	env->envp = ft_realoc_ptr(env->envp, result);
	free(result);
	return (0);
}

void	update_env(t_envirronement *env)
{
	t_env_var	*var;
	t_list		*lst;

	var = NULL;
	lst = env->env_list;
	while (lst)
	{
		var = lst->content;
		if (var != NULL && var->exported == 1)
			check_ptr(env, var->name, var->value);
		if (!lst->next)
			break ;
		lst = lst->next;
	}
}

char	**ft_realoc_ptr(char **tab, char *str)
{
	char	**dest;
	int		i;

	i = 0;
	while (tab[i])
		i++;
	dest = malloc(sizeof(char *) * (i + 2));
	if (dest == NULL)
		return (g_status = MALLOC_ERROR, tab);
	i = 0;
	while (tab[i])
	{
		dest[i] = tab[i];
		i++;
	}
	dest[i++] = ft_strdup(str);
	if (dest[i - 1] == NULL)
		return (g_status = MALLOC_ERROR, NULL);
	dest[i] = NULL;
	free(tab);
	return (dest);
}
