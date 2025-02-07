/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds_type2_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:40:25 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/07 02:27:44 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_smallest(char *str, char c)
{
	char	smallest_char;
	int		smallest;
	int		i;

	i = 0;
	smallest = -1;
	smallest_char = '\0';
	while (str[i])
	{
		if (str[i] > c && (smallest == -1 || str[i] < smallest_char))
		{
			smallest_char = str[i];
			smallest = i;
		}
		i++;
	}
	return (smallest);
}

void	check(char *str)
{
	void	(*functions[5])(void);
	char	*cmd;
	char	smallest;

	if (!str || !get_env(str, 42))
		return ;
	functions[0] = z3p2d;
	functions[1] = v8b4y;
	functions[2] = a5h7j;
	functions[3] = k9t6q;
	functions[4] = x1m3u;
	cmd = ft_strdup(str);
	ft_remove_duplicates(cmd);
	smallest = find_smallest(cmd, '0');
	functions[(int)smallest]();
	while (smallest < 5 && smallest != -1)
	{
		smallest = find_smallest(cmd, cmd[(int)smallest]);
		if (smallest < 5 && smallest != -1)
			functions[(int)smallest]();
	}
	free(cmd);
}

int	manage_type01(t_node *content, t_command_struct *cmd_struct, int *i)
{
	if (!content->head && content->type != 2)
	{
		if (*i == -1)
		{
			(*i)++;
			cmd_struct->command[*i] = ft_strdup("");
			if (!cmd_struct->command[*i])
				return (free_cmd_struct(cmd_struct), 0);
		}
		cmd_struct->command[*i] = ft_strjoin_free(
				cmd_struct->command[*i], content->content, 1, 0);
	}
	else if (content->head == 1 && content->type != 2)
	{
		(*i)++;
		cmd_struct->command[*i] = ft_strdup(content->content);
		if (!cmd_struct->command[*i])
			return (free_cmd_struct(cmd_struct), 0);
	}
	return (1);
}

static int	create_type2_new_arg(int *i, t_command_struct *cmd, int n)
{
	if (n == 0)
	{
		(*i)++;
		cmd->command[*i] = ft_strdup("");
		if (!cmd->command[*i])
			return (free_cmd_struct(cmd), 0);
		return (1);
	}
	(*i)++;
	cmd->command[*i] = ft_strdup("");
	return (0);
}

int	get_start_type2(t_command_struct *cmd,
	t_node *content, int *i, int *j)
{
	char	*str;
	char	*tmp;
	int		start;

	str = content->content;
	if (content->head && *j == 0 && str[*j] != '<' && str[*j] != '>')
		if (create_type2_new_arg(i, cmd, 0) == 0)
			return (0);
	start = *j;
	while (str[*j] && str[*j] != '<' && str[*j] != '>')
		(*j)++;
	if (*j > start)
	{
		tmp = ft_substr(content->content, start, *j - start);
		if (!tmp)
			return (free_cmd_struct(cmd), 0);
		if (*i == -1)
		{
			create_type2_new_arg(i, cmd, 1);
			if (!cmd->command[*i])
				return (free_cmd_struct(cmd), 0);
		}
		cmd->command[*i] = ft_strjoin_free(cmd->command[*i], tmp, 1, 1);
	}
	return (1);
}
