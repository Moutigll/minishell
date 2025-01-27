/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:04:59 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/27 17:40:07 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_func_c(char *command, char **args, t_pipex *pipex)
{
	char	*string;
	int		is_builtin;

	is_builtin = 0;
	// if (!ft_strcmp(command, "echo"))
	// {
	// 	string = echo_command(pipex->cmd_head->list_head);
	// 	printf("%s", string);
	// 	free(string);
	// 	is_builtin = 1;
	// }
	// else if (!ft_strcmp(command, "pwd"))
	// {
	// 	if (args[1])
	// 		ft_putstr_fd("pwd: too many arguments\n", 2);
	// 	else
	// 		printf("%s\n", pipex->cmd_head->main->path);
	// 	is_builtin = 1;
	// }
	return (is_builtin);
}

void	is_func_cmd(char *command,
	char **args, t_pipex *pipex, t_command_head *cmd_head)
{
	int		is_builtin;
	int		error;

	if (!command)
		return ;
	is_builtin = 0;
	// if (!ft_strcmp(command, "env"))
	// 	env_cmd_direct(pipex->cmd_head->main);
	// else if (!ft_strcmp(command, "cd"))
	// 	error = cd_cmd(pipex->cmd_head->envp, args);
	// if (!ft_strcmp(command, "exit") || !ft_strcmp(command, "cd")
	// 	|| !ft_strcmp(command, "export") || !ft_strcmp(command, "unset")
	// 	|| !ft_strcmp(command, "env"))
	// 	is_builtin = 1;
	// else
	is_builtin = exec_func_c(command, args, pipex);
	if (is_builtin)
	{
		clean_pipex(pipex, NULL, 0);
		free_total(cmd_head->list_head, cmd_head->main, cmd_head);
		exit(error);
	}
}
