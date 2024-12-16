/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:05:22 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/16 18:42:39 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	while_space(char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
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
		if (i == -1)
		{
			free(name_var);
			return ;
		}
		while (g_env[i][j] != '=')
			j++;
		write(1, &g_env[i][j + 1], ft_strlen(&g_env[i][j + 1]));
	}
	free(name_var);
}

static char	*check_dollar(char *message, int *i)
{
	char	*result;
	int		j;
	int		n;

	j = 0;
	n = ft_strlen_char(message, ' ');
	if (n > ft_strlen_char(message, '"'))
		n = ft_strlen_char(message, '"');
	(*i)++;
	result = malloc(sizeof(char) * (n + 1));
	while (j < n)
	{
		result[j] = message[j];
		(*i)++;
		j++;
	}
	result[j] = '\0';
	return (result);
}

static void	print_char(int flag, t_block *lst_block, t_list **lst_var)
{
	char	*var;
	int		tmp;
	int		i;

	tmp = 0;
	while (lst_block)
	{
		i = 0;
		if (tmp == 0 && flag)
		{
			i = 2;
			tmp = 1;
			while_space(lst_block->content, &i);
		}
		while (lst_block->content[i])
		{
			if (lst_block->content[i] == '\\')
			{
				write(1, "\\", 1);
				i += 2;
			}
			if (lst_block->content[i] == '$' && lst_block->boolean != 1)
			{
				var = check_dollar(&lst_block->content[i + 1], &i);
				var_echo(var, lst_var);
			}
			if (lst_block->content[i] == '"')
				i++;
			else
				write(1, &lst_block->content[i++], 1);
		}
		if (!lst_block->next)
			break ;
		lst_block = lst_block->next;
	}
	if (!flag)
		write(1, "\n", 1);
}

void	echo_cmd(char *command, t_list **lst_var, t_block **lst_block)
{
	int	flag;
	int	i;

	i = 0;
	flag = 0;
	while (command[i] && command[i] != ' ')
		i++;
	i++;
	while_space(command, &i);;
	if (check_equal("-n", &command[i]))
	{
		i += 3;
		flag = 1;
	}
	while_space(command, &i);
	print_char(flag, *lst_block, lst_var);
}
