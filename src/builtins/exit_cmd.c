/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:00:55 by tle-goff          #+#    #+#             */
/*   Updated: 2025/02/10 18:35:07 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_head(t_head *head)
{
	t_list	*lst_tmp;
	t_node	*node;

	if (!head)
		return ;
	while (head->head)
	{
		node = head->head->content;
		free(node->content);
		free(node);
		lst_tmp = head->head;
		head->head = head->head->next;
		free(lst_tmp);
	}
	free(head);
}

void	free_total(t_main *main, t_command_head *head_main)
{
	free_tab((void **)main->env->envp);
	free_env(main->env->env_list);
	free(main->home);
	free(main->env);
	if (main->path)
		free(main->path);
	if (head_main)
		free(head_main);
	free(main);
}

static int	skip_whitespace_and_sign(char *str, int *sign)
{
	int	i;

	i = 0;
	*sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f' || str[i] == '0')
		i++;
	if (str[i] == '-' || str[i] == '+' || str[i] == '0')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

static int	check_numeric(char *str)
{
	int			i;
	int			sign;
	int			len;
	const char	*max;
	const char	*min;

	max = "9223372036854775807";
	min = "9223372036854775808";
	len = 0;
	i = skip_whitespace_and_sign(str, &sign);
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ')
			return (0);
		if (len > 18 || (len == 18 && ((sign == 1 && str[i] > max[len])
					|| (sign == -1 && str[i] > min[len]))))
			return (0);
		i++;
		len++;
	}
	return (1);
}

static int	check_arguments(char **args, t_pipex *pipex)
{
	if (!args[1])
		return (1);
	if (!check_numeric(args[1]) || args[1][0] == '\0')
	{
		ft_putstr_fd("minicoquille: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		return (pipex->cmd_head->main->error = 2, 1);
	}
	if (args[2])
	{
		ft_putstr_fd("minicoquille: exit: too many arguments\n", STDERR_FILENO);
		return (pipex->cmd_head->main->error = 1, 0);
	}
	return (pipex->cmd_head->main->error = (unsigned)ft_atoi(args[1]) % 256, 1);
}

int	exit_part(t_pipex *pipex, char **args)
{
	t_command_head	*cmd_head;
	int				boolean;
	int				status;

	boolean = 0;
	cmd_head = pipex->cmd_head;
	ft_putstr_fd("exit\n", STDIN_FILENO);
	boolean = check_arguments(args, pipex);
	if (!cmd_head->main->error)
		status = cmd_head->main->old_error;
	else
		status = cmd_head->main->error;
	if (boolean)
	{
		clean_pipex(pipex, NULL, 0);
		free_total(cmd_head->main, cmd_head);
		exit(status);
	}
	return (status);
}
