/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_install.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:38:30 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/16 18:31:05 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*after_quote(char *message)
{
	char	*result;
	int		i;

	i = 0;
	while (message[i] && message[i] != '\'')
		i++;
	result = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (message[i] && message[i] != '\'')
	{
		result[i] = message[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

// static int	count_quote_no(char *message)
// {
// 	int	i;

// 	i = 0;
// 	while (message[i] && message[i] == '\'')
// 		i++;
// 	return (i);
// }

static int	count_quote(char *message, int *j)
{
	int	i;

	i = 0;
	while (message[i] && message[i] == '\'')
		i++;
	*j += i;
	return (i);
}

void	print_block(t_block *lst_block)
{
	while (lst_block)
	{
		printf("%s\n%i\n\n", lst_block->content, lst_block->boolean);
		if (!lst_block->next)
			break ;
		lst_block = lst_block->next;
	}
}

void	main_install_block(t_block **lst_block, char *message)
{
	int		boolean;
	int		quote;
	int		tmp;
	int		i;
	int		j;

	i = 0;
	while (message[i] && message[i] != ' ')
		i++;
	while (message[i] && message[i] == ' ')
		i++;
	quote = -1;
	tmp = i;
	boolean = 0;
	while (message[i])
	{
		if (message[i] == '\'')
		{
			if (quote != -1)
			{
				j = count_quote(&message[i], &i);
				if (quote == j && quote % 2 == 0)
					ft_lst_block_add_back(lst_block, ft_lst_block_new(after_quote(&message[tmp]), 0));
				else
					ft_lst_block_add_back(lst_block, ft_lst_block_new(after_quote(&message[tmp]), 1));
				tmp = i;
				quote = -1;
			}
			else
			{
				ft_lst_block_add_back(lst_block, ft_lst_block_new(after_quote(&message[tmp]), -1));
				quote = count_quote(&message[i], &i);
				tmp = i;
			boolean = 1;
			}
		}
		else
			i++;
	}
	if (!boolean || i == ft_strlen(message))
		ft_lst_block_add_back(lst_block, ft_lst_block_new(after_quote(&message[tmp]), -1));
}
