/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:10:25 by tle-goff          #+#    #+#             */
/*   Updated: 2025/02/10 21:57:44 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_exist(t_list *lst, char *str)
{
	t_env_var	*var;
	int			i;

	i = 0;
	while (lst)
	{
		var = lst->content;
		if (ft_strcmp(var->name, str) == 0)
			return (i);
		if (!lst->next)
			break ;
		lst = lst->next;
		i++;
	}
	return (-1);
}

void	change_var(char *value, int index, t_list *lst)
{
	t_env_var	*var;
	int			i;

	i = 0;
	if (value == NULL)
		return ;
	while (lst)
	{
		var = lst->content;
		if (i == index)
		{
			free(var->value);
			var->value = ft_strdup(value);
			var->exported = 1;
			break ;
		}
		if (!lst->next)
			break ;
		lst = lst->next;
		i++;
	}
}

int	add_var(t_list *lst, t_list *var)
{
	if (var == NULL)
		return (MALLOC_ERROR);
	ft_lstadd_back(&lst, var);
	return (0);
}

static int	count_tab(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	export_cmd(char **args, t_main *main)
{
	int		i;

	i = 1;
	main->error = 0;
	if (ft_strcmp(args[0], "export") == 0)
	{
		if (count_tab(args) == 1)
			main->error = print_ascii_sorted(main->env->env_list);
		else
		{
			while (args[i])
				main->error = check_type_export(args[i++], main->env);
			update_env(main->env);
			change_pwd(main->env->env_list, main->env->envp);
		}
	}
	return (0);
}
