/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:04:59 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/03 15:06:59 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_func_c(char *command, char **args, t_pipex *pipex)
{
	char	*string;
	int		is_builtin;

	is_builtin = 0;
	if (!ft_strcmp(command, "echo"))
	{
		echo_command(args, pipex->cmd_head->main);
		is_builtin = 1;
	}
	else if (!ft_strcmp(command, "pwd"))
	{
		pwd_cmd(args, pipex->cmd_head->main->env);
		is_builtin = 1;
	}
	return (is_builtin);
}

void	is_func_cmd(t_pipex *pipex, int i)
{
	t_command_struct	*cmd;
	t_command_head		*cmd_head;
	int					is_builtin;

	cmd = pipex->cmd_head->cmds[i];
	if (cmd->command[0] == NULL)
		return ;
	is_builtin = 0;
	if (!ft_strcmp(cmd->command[0], "pwd"))
		g_status = cd_cmd(pipex->cmd_head->main->env, cmd->command);
	if (!ft_strcmp(cmd->command[0], "exit") || !ft_strcmp(cmd->command[0], "cd")
		|| !ft_strcmp(cmd->command[0], "export")
		|| !ft_strcmp(cmd->command[0], "unset")
		|| !ft_strcmp(cmd->command[0], "env"))
		is_builtin = 1;
	else
		is_builtin = exec_func_c(cmd->command[0], cmd->command, pipex);
	if (is_builtin)
	{
		cmd_head = pipex->cmd_head;
		clean_pipex(pipex, NULL, 0);
		free_total(cmd_head->main, cmd_head);
		exit(g_status);
	}
}
