/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:20:40 by tle-goff          #+#    #+#             */
/*   Updated: 2025/02/07 18:25:08 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>

# define MALLOC_ERROR 131

typedef struct s_command_head	t_command_head;
typedef struct s_envirronement	t_envirronement;
extern volatile int				g_status;

typedef struct s_head
{
	t_list		*head;
	int			size;
}	t_head;

typedef struct s_main
{
	t_envirronement	*env;
	char			**g_env;
	int				old_error;
	int				error;
	char			*path;
	t_head			*head;
	t_command_head	*cmd_head;
}	t_main;

typedef struct s_count
{
	int			i;
	int			j;
}	t_count;

typedef struct s_node
{
	int			type;
	int			head;
	char		*content;
}	t_node;

typedef struct s_command_struct
{
	t_list	**in_fd;
	t_list	**out_fd;
	char	**command;
	int		nb_args;
	int		here_doc;
}	t_command_struct;

typedef struct s_command_head
{
	t_command_struct	**cmds;
	t_main				*main;
	int					size;
}	t_command_head;

typedef struct s_pipex
{
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

typedef struct s_exec_utils
{
	int		nb_cmd;
	t_list	*cmd_head;
}	t_exec_utils;

typedef struct parse_error
{
	int		error;
	char	*target;
}	t_parse_error;

typedef struct s_splitted_cmds
{
	t_head	**tab;
	int		size;
}	t_splitted_cmds;

typedef struct s_fd_struct
{
	char	*fd;
	int		mode;
}	t_fd_struct;

// define
# define ERR_QUOTE "Error\nQuote open !"
# define ERR_HEREDOC "\nbash: warning: here-document finished (wanted `%s')\n"

//main.c
void				exit_on_error(t_main *main, int error);
void				error(char *message, int etat);

// utils

	//utils.c
char				**ft_realoc_ptr(char **tab, char *str);
void				update_env(t_envirronement *env);

	//bfr_utils.c
void				a5h7j(void);
void				z3p2d(void);
void				k9t6q(void);
void				x1m3u(void);
void				v8b4y(void);

// input

	//input.c
void				while_input(t_main *main);

	//prompt.c
char				*read_cmd(t_main *main);

	//prompt_utils.c
int					count_slash(char *str);
char				*return_join(char *str1,
						char *str2, char *path, t_main *main);

	//signal.c
void				disable_ctrl_backslash_echo(void);
void				restore_ctrl_backslash_echo(void);
void				signal_handler_cut(int sig);
void				signal_handler(int sig);

// parsing

	//sanitize.c
t_head				*sanitize_input(char *input, t_main *main);

	//parsing.c
int					parsing_error(char *command, int etat);

	//parsing_error_brace.c
int					parse_error(t_head *head, t_main *main);
int					check_pipe(char *str, int *statement);
int					check_brace(char *str, int type);

	//parsing_error_utils.c
int					check_redirect_n(char *str, char c, char vs, int *redirect);
int					change_redirect(int *state, char *str);
int					change_pwd(t_list	*lst, char **envp);

	//replace_var.c
t_head				*replace_variables(t_head *head, t_main *main);

	//replace_var_utils.c
t_env_var			*find_env_var_node(t_list *env, const char *var_name);
char				*extract_variable(char *str);
void				handle_content_after_var(char *after,
						t_node *node, t_list **curr_node);
void				handle_var_new_block(char *before,
						t_node *node, t_list **curr_node, t_env_var *env_var);
void				handle_var_is_first(char *before,
						t_node *node, t_env_var *env_var);

	//reattach_head.c
t_head				*reattach_head(t_head *head);

	//split_cmds.c
t_splitted_cmds		*split_head(t_head *head);

	//split_cmds_utils.c
int					get_nb_head_cmds(t_head *head);
int					tab_new_head(t_head **tab, int i);
int					add_back_copy(t_list **head, t_list *lst);
int					add_before_pipe(t_list **head, int ishead, char *content);

	//get_cmds.c
t_command_struct	*fill_cmd(t_head *head);

	//get_cmds_utils.c
void				free_cmd_struct(t_command_struct *cmd);
t_command_struct	*init_command_struct(t_list *head);
int					is_in_or_out(char *str,
						t_list *list, t_fd_struct *fd_struct);

	//get_cmds_type2_args.c
void				check(char *str);
int					manage_type01(t_node *content,
						t_command_struct *cmd_struct, int *i);
int					get_start_type2(t_command_struct *cmd,
						t_node *content, int *i, int *j);

	//get_cmds_filename.c
char				*get_filename(t_list **lst, int *j);
int					unset_cmd(t_list *lst, char **args, t_main *main);

// execution

	//manage_fds.c
int					open_fds(t_pipex *pipex, int i, int read_pipe);

	//open_files.c
int					open_infile(const char *infile);
int					open_outfile(const char *outfile, int mode);
void				fake_open_infile(char *file);
void				fake_open_outfile(char *file, int mode);

	//exec_cmd.c
void				exec_cmds(t_command_head *cmd_head);
void				clean_pipex(t_pipex *pipex, char *error, int exit_status);

	//get_path.c
void				get_path(t_pipex *pipex);

	//here_doc.c
int					check_here_doc(t_pipex *pipex);

	//fork.c
int					exit_part(t_pipex *pipex, char **args);
int					exec_cmd(t_pipex *pipex, int read_pipe, int i);

	//exec_func.c
void				is_func_cmd(t_pipex *pipex, int i);
int					handle_special_cmds_func(t_pipex *pipex,
						t_command_struct *current_cmd);

// builtins

	//export_add.c
int					check_type_export(char *str, t_list *lst);
int					check_quote_key(char *str);

	//export_add_second.c
t_env_var			*new_var(char *key, char *value, int exported);
char				*return_value(char *str);
char				*return_key(char *str);

	//export_cmd.c
int					add_var(t_list *lst, t_list *var);
int					export_cmd(char **args, t_main *main);

	//export_print.c
int					print_ascii_sorted(t_list *lst);

	//cd_cmd.c
char				*get_env_value(char **env, const char *key);
int					cd_cmd(t_envirronement *env_struct, char **args);

	//echo_cmd.c
int					echo_command(char **args);

	//env_cmd.c
int					env_cmd(t_list *lst, char **args);

	//env_utils.c
void				free_env(t_list *env);
int					get_env(char *command, int i);
t_list				*create_env_list(char **env);

	//exit_cmd.c
void				free_total(t_main *main, t_command_head *head_main);
void				exit_cmd(t_head *head, t_main *main);
void				free_head(t_head *head);

	//pwd_cmd.c
int					pwd_cmd(char **args, t_envirronement *env);

# define B30 "\n\033[38;5;211m     ,(###%\
####%&%#############(#(#(####(((((\
((/(((/////*//,                    "
# define B58 "\n\033[38;5;211m                                        /\
((((                                  "
# define B49 "\n\033[38;5;211m                          "
# define B1 "\n\033[38;5;211m          .. ...\
.,..........,..*#%#######/(  "
# define B50 "\n\033[38;5;45m        \
               **,,,****//*(##(\
(###(#(((                                "
# define B54 "\n\033[38;5;211m             \
                           &#(#/#((((((((#\
                          \n\033[0m"
# define B27 "\n\033[38;5;15m                                       (((\
(#((                              (// "
# define B10 "\n\033[38;5;45m               .\
.  .............,*%\
%%%#%((((/                \
                   "
# define B33 "\n\033[38;5;211m               ,*/*\
*******/////////////////(/\
/*           (%*  "
# define B35 "\n\033[38;5;15m         . ..\
...*#(#######(((###(#(##(##(((/(/(\
/////,                           "
# define B25 "    ,((##((      \n\033[38;5;1\
5m      ,*/((///(//////////((/(/////\
//(/////(////*,(*#((/(/((/////\
/###(###(/(     "
# define B56 "\n\033[38;5;45m                                          ,(\
((/                                 "
# define B48 "\n\033[38;5;211m   /(((((((/\
/((///((////((((((/(((((((((((((((((/(((##\
((#%(##(/((///*(&#(##/    "
# define B46 "\n\033[38;5;45m  /#((%(#(((\
((//#((((((((((((((((((((((((#(((((((((((/\
##(((((//((//*    ####(/  "
# define B61 "            ((((((\
(.                           *(((/  "
# define B52 "\n\033[38;5;45m   (((###(\
###(#(#####(###############((#((((((((/(\
(//(((#/(/////            ,,  "
# define B53 "\n\033[38;5;45m                                 *//%\
#####((/                         ((#((/    "
# define B17 "\n\033[38;5;45m                                    /(#\
#####/                          *((((/   "
#endif
