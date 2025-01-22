/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:20:40 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/23 00:35:36 by ele-lean         ###   ########.fr       */
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
# include <errno.h>

# define MALLOC_ERROR 131

typedef struct s_command_head	t_command_head;
typedef struct s_envirronement	t_envirronement;

typedef struct s_head
{
	t_list		*head;
	int			size;
}	t_head;

typedef struct s_main
{
	t_envirronement	*env;
	t_list			*lst_var;
	char			**g_env;
	char			*path;
	int				error;
	t_head			*head;
	t_command_head	*cmd_head;
}	t_main;

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
	int			out_mode;
	t_head		*list_head;
	t_main		*main;
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
	int				stdin_backup;
	int				stdout_backup;
	pid_t			*pid_tab;
	t_command_head	*cmd_head;
}	t_pipex;

typedef struct s_malloc
{
	int	boolean;
	int	count;
	int	tab;
	int	i;
	int	j;
}	t_malloc;

void			print_arg(char **str);

// define
# define ERR_QUOTE "Error\nQuote open !"

// main.c
void			exit_on_error(t_main *main, int error);
void			error(char *message, int etat);
void			print_list(t_list *lst);

// env_cmd.c
int				env_cmd(t_head *head, t_main *main);
void			env_cmd_direct(t_main *main);

// export_cmd.c
int				find_block(t_head *head,
					int *n, char **content_block, int boolean);
int				export_cmd(t_head *head, t_main *main);
t_head			*return_head(t_head *head, int i);
t_list			*return_lst(t_head *head, int i);

// signal.c
void			signal_handler(int sig);

// unset.c
int				unset_cmd(t_head *head, t_main *main);

// realoc.c
char			**ft_realoc_ptr_unset(char **tab, int n);
int				search_env(t_main *main, char *content);
char			**ft_realoc_ptr(char **tab, char *str);
char			*return_before(char *content);

// pwd_cmd.c
int				pwd_cmd(t_head *head);

// fd_take.c
char			**return_fd(char *content, char *c);

// exit_cmd.c
void			free_total(t_head *head,
					t_main *main, t_command_head *head_main);
void			exit_cmd(t_head *head, t_main *main);
void			free_head(t_head *head);

// cd_cmd.c
int				cd_cmd(char **env, char **args);

// detect_var.c
int				verif_var(t_head *head, t_main *main, int n);

// parsing_var.c
int				search_exist(char *name_var, char **g_env);
void			replace_var(t_head **head, t_main *main);
char			*return_name_var(char *content, char c);

// attach.c
char			*attach_block_quote(t_head *head);
char			*attach_block(t_head *head);

// prompt_2.c
int				return_slash(char *str);

// ft_listnode.c
void			ft_listnode(t_list **lst_tmp, int tab);

// check_equal.c
int				check_equal(char *format, t_head *head, int tab);

// decomp.c
t_command_head	*return_main(t_head *head, t_main *main);

// echo_cmd.c
char			*echo_command(t_head *head);

// input.c
void			while_input(t_main *main);

// prompt.c
char			*read_cmd(t_main *main);

// parsing.c
int				parsing_error(char *command, int etat);

// sanitize.c
t_head			*sanitize_input(char *input, t_main *main);

// file_tmp.c
void			print_block(t_head *head);

// exec_cmd.c
void			exec_cmds(t_command_head *cmd_head);

// open_files.c
void			open_fds(t_pipex *pipex, t_command_head *head);
void			fake_open_infile(char *file);
void			fake_open_outfile(char *file, int mode);

// get_path.c
void			get_path(t_pipex *pipex);

// fork.c
void			exec_cmd(t_pipex *pipex, int i, char **envp);

// exec_utils.c
void			clean_pipex(t_pipex *pipex, char *error, int exit_status);
void			handle_here_doc(char *delimiter, t_pipex *pipex);
void			init_pipex(t_pipex *pipex, t_command_head *cmd_head);

// exec_func.c
void			is_func_cmd(char *command,
					char **args, t_pipex *pipex, t_command_head *cmd_head);






typedef struct s_env_var
{
	char	*name;
	char	*value;
	int		exported;
}	t_env_var;

typedef struct s_envirronement
{
	t_list	*env_list;
	char	**envp;
}	t_envirronement;

// env_utils.c
void				free_env(t_list *env);
t_list				*create_env_list(char **env);
void				print_env(t_list *env);

// env_var.c
//static t_env_var	*find_env_var_node(t_list *env, const char *var_name);
t_head				*replace_variables(t_head *head, t_envirronement *env);

// reattach_head.c
t_head				*reattach_head(t_head *head);

#endif
