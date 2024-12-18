/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:20:40 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/18 16:59:37 by tle-goff         ###   ########.fr       */
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

// input.c
void	while_input(t_main **main);

// prompt.c
char	*read_cmd(void);

// parsing.c
int		parsing_error(char *command, int etat);

// TESTER GLOBAL
void	main_tester_traitment(int argc, char **argv);
void	tester_quote(void);

#endif
