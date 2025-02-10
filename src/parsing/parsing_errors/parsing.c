/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:23:49 by tle-goff          #+#    #+#             */
/*   Updated: 2025/02/10 19:05:35 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_redirect(int *redirect, int count)
{
	*redirect = 0;
	if (count > 0)
		*redirect = 1;
}

int	parsing_error(char *command, int etat)
{
	int	quote_1;
	int	quote_2;
	int	i;

	i = 0;
	quote_1 = -1;
	quote_2 = -1;
	while (command[i])
	{
		if (command[i] == '\"' && quote_2 < 0)
			quote_1 *= -1;
		else if (command[i] == '\'' && quote_1 < 0)
			quote_2 *= -1;
		i++;
	}
	if ((quote_1 > 0 || quote_2 > 0))
		return (error(ERR_QUOTE, etat), 0);
	return (1);
}
