/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:56:22 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/16 17:02:01 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_name_var(char *command)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (command[i] && command[i] != '=')
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		dest[j] = command[j];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

int	search_exist(char *name_var)
{
	int	i;
	int	j;

	i = 0;
	while (g_env[i])
	{
		j = 0;
		while (g_env[i][j] && g_env[i][j] == name_var[j] && g_env[i][j] != '=')
			j++;
		if (j == ft_strlen(name_var))
			return (i);
		i++;
	}
	return (-1);
}

int	lst_look_word(t_list *lst_var, char *var)
{
	int	i;

	i = 0;
	while (lst_var)
	{
		if (strcmp((const char *)lst_var->name_var, (const char *)var) == 0)
			return (i);
		if (!lst_var->next)
			break ;
		lst_var = lst_var->next;
		i++;
	}
	return (-1);
}

static void	export_lst_var(t_list **lst_var, char *var)
{
	char	*second_add;
	char	*first_add;
	char	*tmp_2;
	char	*tmp;
	int		j;

	if (lst_look_word(*lst_var, var) == -1)
		return ;
	tmp_2 = ft_strdup(lst_returnn(*lst_var, lst_look_word(*lst_var, var))->name_var);
	first_add = ft_strjoin(tmp_2, "=");
	free(tmp_2);
	tmp = ft_strdup(lst_returnn(*lst_var, lst_look_word(*lst_var, var))->content);
	second_add = ft_strjoin(first_add, tmp);
	free(tmp);
	free(first_add);
	j = search_exist(lst_returnn(*lst_var, lst_look_word(*lst_var, var))->name_var);
	if (j >= 0)
	{
		free(g_env[j]);
		g_env[j] = second_add;
	}
	else
		g_env = ft_realoc_ptr(g_env, second_add);
	free(second_add);
	free_node(lst_var, lst_look_word(*lst_var, var));
}

void	*export_cmd(char *command, t_list **lst_var)
{
	char	*name_var;
	int		i;
	int		j;

	i = 6;
	while_space(command, &i);
	if (ft_strchr(&command[i], '=') == NULL)
		return (export_lst_var(lst_var, &command[i]), NULL);
	name_var = get_name_var(&command[i]);
	if (name_var[0] == '\0')
		return (free(name_var), NULL);
	j = search_exist(name_var);
	free(name_var);
	if (j >= 0)
	{
		free(g_env[j]);
		g_env[j] = ft_strdup(ft_strdup(&command[i]));
	}
	else
		g_env = ft_realoc_ptr(g_env, &command[i]);
	return (NULL);
}
