/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:39:13 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/17 13:21:56 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../get_next_line/get_next_line.h"
# include "readline/readline.h"
# include "readline/history.h"
# include "unistd.h"
# include "signal.h"
# include "stdlib.h"
# include "stdio.h"
# include "fcntl.h"

extern char	**g_env;

// boolean struct
typedef struct	s_boolean
{
	int	boolean_1;
	int	boolean_2;
	int	boolean_3;
}	t_boolean;

// list var
typedef struct	s_list
{
	char			*name_var;
	char			*content;
	struct s_list	*next;
}	t_list;

// list block
typedef struct	s_block
{
	char			*content;
	int				boolean;
	struct s_block	*next;
}	t_block;

// main.c
void	while_main(t_list **lst_var, char **last_cmd, t_block **lst_block);
int		main(int argc, char **argv, char **env);

// export_cmd.c
void	*export_cmd(char *command, t_list **lst_var);
int		lst_look_word(t_list *lst_var, char *var);
int		search_exist(char *name_var);
char	*get_name_var(char *command);

// gest_var.c
void	replace_var_lst(t_list **lst_var, char *content, int tab);
void	change_direct(char *name_var, char *content);
char	*remove_double_quote(char *content);

// unset_cmd.c
void	unset_cmd(char *command);

// prompt.c
char	*prompt_return(char *path);
int		return_slash(char *str);

// cd_cmd.c
void	cd_cmd(char *command);

// read_enter.c
char	*read_cmd(void);

// pwd_cmd.c
void	pwd_cmd(void);

// env_cmd.c
void	print_env(void);

// echo_cmd.c
void	echo_cmd(char *command, t_list **lst_var, t_block **lst_block);
void	var_echo(char *name_var, t_list **lst_var);
char	*check_dollar(char *message, int *i);
void	while_space(char *str, int *i);

// gest_cmd.c
int		check_equal(char *str1, char *str2);
void	cmd_format(char *command, t_list **lst_var, char **last_cmd, t_block **lst_block);

// signal.c
char	*ft_last_cmd(char *last_cmd, char *command);
void	signal_interception(int sig);

// free_function.c
void	free_env(void);

// block_install.c
void	main_install_block(t_block **lst_block, char *message);
void	print_block(t_block *lst_block);

// /utils
void	ft_lst_block_add_back(t_block **lst, t_block *new);
int		ft_lstcheckisin(t_list *lst_var, char *name_var);
int		ft_strcmp(const char *s1, const char *s2);
t_list	*ft_lstnew(char	*name_var, char	*content);
void	ft_lstadd_back(t_list **lst, t_list *new);
char	**ft_realoc_ptr_unset(char **tab, int n);
t_block	*ft_lst_block_new(char *content, int i);
char	**ft_realoc_ptr(char **tab, char *str);
t_list	*lst_returnn(t_list *lst_var, int n);
char	*ft_strjoin(char *str1, char *str2);
void	free_node(t_list **lst, int index);
int		ft_strlen_char(char *str, char c);
void	ft_lst_block_clear(t_block **lst);
char	*ft_strchr(const char *s, int c);
t_block	*ft_lst_block_last(t_block *lst);
char	*ft_strcut(char *str, char c);
void	ft_lstclear(t_list **lst);
t_list	*ft_lstlast(t_list *lst);
char	*ft_strdup(char *str);
int		ft_strlen(char *str);

#endif
