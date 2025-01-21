/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:30:38 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/21 16:24:08 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	init_and_prepare_pipex(t_pipex **pipex, t_command_head *cmd_head)
{
	*pipex = malloc(sizeof(t_pipex));
	if (!(*pipex))
		return (clean_pipex(NULL, "Malloc error", MALLOC_ERROR));
	init_pipex(*pipex, cmd_head);
	open_fds(*pipex, cmd_head);
	if (cmd_head->here_doc && !cmd_head->error)
		handle_here_doc(cmd_head->here_doc, *pipex);
	if (!cmd_head->error)
		get_path(*pipex);
}

static pid_t	*allocate_pid_table(t_pipex *pipex, t_command_head *cmd_head)
{
	pid_t	*pid_tab;

	pid_tab = malloc(sizeof(pid_t) * cmd_head->size);
	if (!pid_tab)
		clean_pipex(pipex, "Malloc error", MALLOC_ERROR);
	return (pid_tab);
}

static void	execute_all_commands(t_pipex *pipex,
	t_command_head *cmd_head)
{
	int	i;

	i = 0;
	while (i < cmd_head->size)
	{
		exec_cmd(pipex, i, cmd_head->envp);
		i++;
	}
}

static void	wait_for_children(t_pipex *pipex, t_command_head *cmd_head)
{
	int		status;
	int		i;

	i = 0;
	while (i < cmd_head->size)
	{
		if (waitpid(pipex->pid_tab[i], &status, 0) == -1)
		{
			perror("waitpid: ");
			cmd_head->error = 1;
			return ;
		}
		if (WIFEXITED(status))
			cmd_head->error = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			cmd_head->error = 128 + WTERMSIG(status);
		i++;
	}
}

void	exec_cmds(t_command_head *cmd_head)
{
	t_pipex	*pipex;

	if (!cmd_head || !cmd_head->head)
		return ;
	init_and_prepare_pipex(&pipex, cmd_head);
	if (cmd_head->error || !pipex)
		return ;
	pipex->pid_tab = allocate_pid_table(pipex, cmd_head);
	if (!pipex->pid_tab)
		return ;
	execute_all_commands(pipex, cmd_head);
	wait_for_children(pipex, cmd_head);
	clean_pipex(pipex, NULL, cmd_head->error);
}
