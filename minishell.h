/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:20:40 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/28 14:38:39 by tle-goff         ###   ########.fr       */
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

extern volatile int		g_status;

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

typedef struct s_command_struct
{
	t_list	**in_fd;
	t_list	**out_fd;
	char	**command;
	int		nb_args;
}	t_command_struct;


void			print_arg(char **str);

// define
# define ERR_QUOTE "Error\nQuote open !"

// main.c
void			exit_on_error(t_main *main, int error);
void			error(char *message, int etat);
void			print_list(t_list *lst);

// env_cmd.c
int				env_cmd(t_list *lst, char **args);

// export_add.c
void			check_type_export(char *str, t_list *lst);

// parsing.c
int				parsing_error(char *command, int etat);

// parsing_error_brace.c
int				check_pipe(char *str, int *statement);;
int				check_brace(char *str, int type);
int				parse_error(t_head *head);

// export_print.c
t_list			*find_min_node(t_list *lst, t_list *visited);
int				print_ascii_sorted(t_list *lst);

// export_add_second.c
t_env_var		*new_var(char *str, char *key, char *value, int exported);
char			*return_value(char *str);
int				check_first_char(char c);
char			*return_key(char *str);

// export_cmd.c
int				export_cmd(t_list *lst, char **args );

// signal.c
void			signal_handler(int sig);

// pwd_cmd.c
int				pwd_cmd(char **args);

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

// prompt_2.c
int				return_slash(char *str);

// ft_listnode.c
void			ft_listnode(t_list **lst_tmp, int tab);

// check_equal.c
int				check_equal(char *format, t_head *head, int tab);

// decomp.c
t_command_head	*return_main(t_head *head, t_main *main);

// echo_cmd.c
void			echo_command(char **args);

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

// unset_cmd.c
int				unset_cmd(t_list *lst , char **args);

// exec_func.c
void			is_func_cmd(char *command,
					char **args, t_pipex *pipex, t_command_head *cmd_head);

// env_utils.c
void				free_env(t_list *env);
int					get_env(char *command, int i);
t_list				*create_env_list(char **env);
void				print_env(t_list *env);

// env_var.c
//static t_env_var	*find_env_var_node(t_list *env, const char *var_name);
t_head				*replace_variables(t_head *head, t_envirronement *env);

// reattach_head.c
t_head				*reattach_head(t_head *head);
void				print_head(t_list *head);

// split_cmds.c
t_splitted_cmds		*split_head(t_head *head);

// split_cmds_utils.c
int					get_nb_head_cmds(t_head *head, t_parse_error *error);
int					tab_new_head(t_head **tab, int i);
int					add_back_copy(t_list **head, t_list *lst);
int					add_before_pipe(t_list **head, int ishead, char *content);

// clean_cmd.c
void				cleant_tab_cmd(t_head **tab);

// get_cmds.c
t_command_struct	*fill_cmd(t_head *head);

// get_cmds_utils.c
void				free_cmd_struct(t_command_struct *cmd);
t_command_struct	*init_command_struct(t_list *head);
int					is_in_or_out(char *str,
						t_list *list, t_fd_struct *fd_struct);

// get_cmds_filename.c
char				*get_filename(t_list **lst, int *j);


// bfr_utils.c
void				a5h7j(void);
void				z3p2d(void);
void				k9t6q(void);
void				x1m3u(void);
void				v8b4y(void);

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
