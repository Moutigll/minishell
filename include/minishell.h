/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:20:40 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/06 11:37:20 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include "readline/readline.h"
# include "readline/history.h"
# include "signal.h"
# include "stdio.h"
# include <sys/wait.h>

typedef struct s_head
{
	t_list		*head;
	int			size;
}	t_head;

typedef struct s_node
{
	int			type;
	int			head;
	char		*content;
}	t_node;

typedef struct s_command_head
{
	t_list		*head;
	char		*in_fd;
	char		*out_fd;
	char		**envp;
	char		*here_doc;
	int			size;
	int			error;
}	t_command_head;

typedef struct s_command
{
	char		*command;
	char		**args;
}				t_command;

typedef struct s_pipex
{
	int				in_fd;
	int				out_fd;
	int				pipe_fd[2];
	t_command_head	*cmd_head;
}	t_pipex;

typedef struct s_main
{
	t_list	*lst_var;
	char	**g_env;
}	t_main;

// define
# define ERR_QUOTE "Error\nQuote open !"

// main.c
void	error(char *message, int etat);
void	print_list(t_list *lst);

// export_cmd.c
int		export_cmd(t_head *head, t_main **main);
t_head	*return_head(t_head *head, int i);
t_list	*return_lst(t_head *head, int i);

// detect_var.c
void	verif_var(t_head *head, t_main **main);

// parsing_var.c
int		search_exist(char *name_var, char **g_env);
void	replace_var(t_head **head, t_main *main);
char	*return_name_var(char *content, char c);

// ft_listnode.c
void	ft_listnode(t_list **lst_tmp, int tab);

// check_equal.c
int		check_equal(char *format, t_head *head, int tab);

// echo_cmd.c
char	*echo_command(t_head *head);

// input.c
void	while_input(t_main **main);

// prompt.c
char	*read_cmd(void);

// parsing.c
int		parsing_error(char *command, int etat);

// sanitize.c
t_head	*sanitize_input(char *input);

// file_tmp.c
void	print_block(t_head *head);

// exec_cmd.c
void	exec_cmds(t_command_head *cmd_head);
void	clean_pipex(t_pipex *pipex, char *error, int exit_status);

// open_files.c
void	open_fds(t_pipex *pipex, t_command_head *head);

// get_path.c
void	get_path(t_pipex *pipex);

// fork.c
void	exec_cmd(t_pipex *pipex, int i, char **envp);

#endif
