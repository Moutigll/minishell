/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:33:18 by tle-goff          #+#    #+#             */
/*   Updated: 2025/02/05 11:27:25 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "termios.h"

void	disable_ctrl_backslash_echo(void)
{
	struct termios	term;

	if (isatty(STDIN_FILENO))
	{
		tcgetattr(STDIN_FILENO, &term);
		term.c_lflag &= ~0001000;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
}

void	restore_ctrl_backslash_echo(void)
{
	struct termios	term;

	if (isatty(STDIN_FILENO))
	{
		tcgetattr(STDIN_FILENO, &term);
		term.c_lflag |= 0001000;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
}

void	signal_handler_cut(int sig)
{
	if (sig == SIGINT)
	{
		g_status = -1;
		printf("^C\n");
		close(STDIN_FILENO);
	}
	(void)sig;
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 1;
	}
	else if (sig == SIGQUIT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}
