/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:04:59 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/05 19:54:04 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_func_c(char *command, char **args, t_pipex *pipex)
{
	if (!ft_strcmp(command, "echo"))
		pipex->cmd_head->main->error = echo_command(args);
	else if (!ft_strcmp(command, "pwd"))
		pipex->cmd_head->main->error = pwd_cmd(args,
				pipex->cmd_head->main->env);
	else if (!ft_strcmp(command, "cd"))
		pipex->cmd_head->main->error = cd_cmd(pipex->cmd_head->main->env,
				args);
	else if (!ft_strcmp(command, "export"))
		pipex->cmd_head->main->error = export_cmd(args,
				pipex->cmd_head->main);
	else if (!ft_strcmp(command, "unset"))
		pipex->cmd_head->main->error
			= unset_cmd(pipex->cmd_head->main->env->env_list,
				args, pipex->cmd_head->main);
	else if (!ft_strcmp(command, "env"))
		pipex->cmd_head->main->error
			= env_cmd(pipex->cmd_head->main->env->env_list, args);
	else if (!ft_strcmp(command, "exit"))
		pipex->cmd_head->main->error = exit_part(pipex, args);
}

void	is_func_cmd(t_pipex *pipex, int i)
{
	t_command_struct	*cmd;
	t_command_head		*cmd_head;
	int					is_builtin;
	int					status;

	is_builtin = 0;
	cmd = pipex->cmd_head->cmds[i];
	if (cmd->command[0] == NULL)
		return ;
	if (!ft_strcmp(cmd->command[0], "exit") || !ft_strcmp(cmd->command[0], "cd")
		|| !ft_strcmp(cmd->command[0], "export")
		|| !ft_strcmp(cmd->command[0], "unset")
		|| !ft_strcmp(cmd->command[0], "env")
		|| !ft_strcmp(cmd->command[0], "echo")
		|| !ft_strcmp(cmd->command[0], "pwd"))
		is_builtin = 1;
	exec_func_c(cmd->command[0], cmd->command, pipex);
	if (is_builtin)
	{
		status = pipex->cmd_head->main->error;
		cmd_head = pipex->cmd_head;
		clean_pipex(pipex, NULL, 0);
		free_total(cmd_head->main, cmd_head);
		exit(status);
	}
}

int	handle_special_cmds_part2(t_pipex *pipex,
	t_command_struct *current_cmd)
{
	if (current_cmd->command[0] == NULL)
		return (0);
	else if (ft_strcmp("unset", current_cmd->command[0]) == 0)
		unset_cmd(pipex->cmd_head->main->env->env_list,
			current_cmd->command, pipex->cmd_head->main);
	else if (ft_strcmp("export", current_cmd->command[0]) == 0)
		export_cmd(current_cmd->command, pipex->cmd_head->main);
	else if (ft_strcmp("cd", current_cmd->command[0]) == 0)
		pipex->cmd_head->main->error = cd_cmd(pipex->cmd_head->main->env,
				current_cmd->command);
	else if (ft_strcmp("env", current_cmd->command[0]) == 0)
		pipex->cmd_head->main->error
			= env_cmd(pipex->cmd_head->main->env->env_list,
				current_cmd->command);
	else if (ft_strcmp("exit", current_cmd->command[0]) == 0)
		pipex->cmd_head->main->error = exit_part(pipex,
				current_cmd->command);
	else
		return (0);
	return (1);
}
