/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error_brace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:15:13 by tle-goff          #+#    #+#             */
/*   Updated: 2025/02/10 19:04:00 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_pipe(char *str, int *statement)
{
	int	i;

	i = 0;
	if (str[0] == '|' && *statement == 1)
		return (ft_putstr_fd("minicoquille: ", 2),
			ft_putstr_fd(ERR_PIPE, 2), 1);
	*statement = 0;
	while (str[i])
	{
		if (str[i] == '|' && str[i + 1] == '|')
			return (ft_putstr_fd("minicoquille: ", 2),
				ft_putstr_fd(ERR_PIPE, 2), 1);
		i++;
	}
	if (i > 0 && str[i - 1] == '|')
		*statement = 1;
	return (0);
}

static int	check_closing_brace(char *str, int i, int *j, int *brace)
{
	while (ft_isalnum(str[i + *j]) || str[i + *j] == '_')
		(*j)++;
	if (str[i + *j] != '}')
		return (1);
	(*brace)++;
	return (0);
}

int	check_brace(char *str, int type)
{
	int	brace;
	int	i;
	int	j;

	i = 0;
	brace = 0;
	while (str[i])
	{
		j = 0;
		if (brace == 0 && str[i] == '{' && i > 0 && str[i - 1] == '$')
		{
			if (check_closing_brace(str, i, &j, &brace) == 1)
				return (1);
		}
		else if (brace > 0 && str[i] == '{')
			return (1);
		if (brace > 0 && str[i] == '}')
			brace = 0;
		else if (brace == 0 && (str[i] == '{' || str[i] == '}') && type == 2)
			return (1);
		i++;
	}
	if (brace > 0)
		return (1);
	return (0);
}
