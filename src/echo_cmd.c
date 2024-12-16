/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:05:22 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/13 13:34:40 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*check_dollar(char *message, int *i)
{
	char	*var;
	int		n;
	int		j;

	j = 0;
	(*i)++;
	if (message[*i] == '"')
		return (NULL);
	n = ft_strlen_char(&message[*i], ' ');
	var = malloc(sizeof(char) * (n + 1));
	while (j < n)
	{
		var[j] = message[*i];
		(*i)++;
		j++;
	}
	var[j] = '\0';
	return (var);
}

static void	var_echo(char *name_var, t_list **lst_var)
{
	char	*content;
	int		i;
	int		j;

	j = 0;
	if (!name_var)
		return ;
	i = ft_lstcheckisin(*lst_var, name_var);
	if (i >= 0)
	{
		content = lst_returnn(*lst_var, i)->content;
		write(1, content, ft_strlen(content));
	}
	else
	{
		i = search_exist(name_var);
		while (g_env[i][j] != '=')
			j++;
		write(1, &g_env[i][j + 1], ft_strlen(&g_env[i][j + 1]));
	}
	free(name_var);
}

static void	print_char(char *message, int j, t_list **lst_var)
{
	char	*var;
	int		i;

	i = 0;
	while (message[i])
	{
		if (message[i] == 92 && message[i + 1] == 92)
		{
			i += 2;
			write(1, "\\", 1);
		}
		if (message[i] == '$')
		{
			var = check_dollar(message, &i);
			var_echo(var, lst_var);
		}
		else if (message[i] != 92)
			write(1, &message[i++], 1);
		else
			i++;
	}
	if (j == 0)
		write(1, "\n", 1);
}

void	while_space(char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
}

void	echo_cmd(char *command, t_list **lst_var)
{
	int	flag;
	int	i;

	i = 4;
	flag = 0;
	while_space(command, &i);
	if (check_equal("-n", &command[i]))
	{
		i += 3;
		flag = 1;
	}
	while_space(command, &i);
	if (flag)
		print_char(&command[i], 1, lst_var);
	else
		print_char(&command[i], 0, lst_var);
}
