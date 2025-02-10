/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:57:00 by tle-goff          #+#    #+#             */
/*   Updated: 2025/02/10 18:45:34 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#include "../include/minishell.h"

int	handle_here_doc_start(int pipe_fd[2],
	t_pipex *pipex)
{
	signal(SIGINT, signal_handler_cut);
	signal(SIGQUIT, signal_handler_cut);
	disable_ctrl_backslash_echo();
	write(1, "> ", 2);
	if (pipe(pipe_fd) == -1)
		return (clean_pipex(pipex, "Pipe error", 32), -1);
	return (0);
}

char	*replace_error(t_main *main, char *str, char *var)
{
	char	*new_str;
	char	*value;

	value = ft_itoa(main->error);
	new_str = ft_str_replace(str, var, value);
	free(value);
	return (new_str);
}

char	*return_var(int i, char *str, char *var_name)
{
	char	*var;

	var = ft_strdup("$");
	if (str[i + 1] == '{')
		var = ft_strjoin_free(var, "{", 1, 0);
	var = ft_strjoin_free(var, var_name, 1, 0);
	return (var);
}

char	*return_new_str(char *var, char *str, char *var_name, char *new_str)
{
	free(var);
	free(var_name);
	free(str);
	return (new_str);
}

char	*set_var(int i, char *str, char *var_name)
{
	char	*var;

	var = return_var(i, str, var_name);
	if (str[i + 1] == '{')
		var = ft_strjoin_free(var, "}", 1, 0);
	return (var);
}
