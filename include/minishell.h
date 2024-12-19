/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:20:40 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/19 15:10:48 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include "readline/readline.h"
# include "readline/history.h"
# include "unistd.h"
# include "signal.h"
# include "stdlib.h"
# include "stdio.h"
# include "fcntl.h"

typedef struct 	s_head
{
	t_list		*head;
	int			size;
}	t_head;

typedef struct 	s_node
{
	int			type;
	int			head;
	char		*content;
}	t_node;

typedef struct s_main
{
	char	**g_env;
}	t_main;

// define
# define ERR_QUOTE "Error\nQuote open !"

// main.c
void	error(char *message, int etat);

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

// TESTER GLOBAL
void	main_tester_traitment(int argc, char **argv);
void	tester_quote(void);
void	tester_block(void);

#endif
