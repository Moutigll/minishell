/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_install.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:38:30 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/17 14:11:57 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*after_quote(char *message, char c)
{
	char	*result;
	int		i;

	i = 0;
	while (message[i] && message[i] != c)
		i++;
	result = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (message[i] && message[i] != c)
	{
		result[i] = message[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static int	count_quote(char *message, int *j, char c)
{
	int	i;

	i = 0;
	while (message[i] && message[i] == c)
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
	t_boolean	*boolean;
	int			quote;
	int			tmp;
	int			i;
	int			j;

	i = 0;
	boolean = malloc(sizeof(t_block));
	boolean->boolean_1 = 0;
	boolean->boolean_2 = 0;
	boolean->boolean_3 = 0;
	while (message[i])
	{
		if (message[i] == '\'' || message[i] == '\"')
			break ;
		i++;
	}
	if (ft_strlen(message) == i)
	{
		ft_lst_block_add_back(lst_block, ft_lst_block_new(ft_strdup(&message[0]), -1));
		return ;
	}
	i = 0;
	quote = -1;
	tmp = i;
	while (message[i])
	{
		if (message[i] == '"' && !boolean->boolean_2)
		{
			if (quote != -1)
			{
				j = count_quote(&message[i], &i, '\"');
				ft_lst_block_add_back(lst_block, ft_lst_block_new(after_quote(&message[tmp], '\"'), 0));
				tmp = i;
				quote = -1;
				boolean->boolean_3 = 0;
			}
			else
			{
				ft_lst_block_add_back(lst_block, ft_lst_block_new(after_quote(&message[tmp], '\"'), -1));
				quote = count_quote(&message[i], &i, '\"');
				tmp = i;
				boolean->boolean_1 = 1;
				boolean->boolean_3 = 1;
			}
		}
		else if (message[i] == '\'' && !boolean->boolean_3)
		{
			if (quote != -1)
			{
				j = count_quote(&message[i], &i, '\'');
				if (quote == j && quote % 2 == 0)
					ft_lst_block_add_back(lst_block, ft_lst_block_new(after_quote(&message[tmp], '\''), 0));
				else
					ft_lst_block_add_back(lst_block, ft_lst_block_new(after_quote(&message[tmp], '\''), 1));
				tmp = i;
				quote = -1;
				boolean->boolean_2 = 0;
			}
			else
			{
				ft_lst_block_add_back(lst_block, ft_lst_block_new(after_quote(&message[tmp], '\''), -1));
				quote = count_quote(&message[i], &i, '\'');
				tmp = i;
				boolean->boolean_1 = 1;
				boolean->boolean_2 = 1;
			}
		}
		else
			i++;
	}
	if (!boolean->boolean_1)
		ft_lst_block_add_back(lst_block, ft_lst_block_new(ft_strdup(&message[tmp]), -1));
	// else if (i == ft_strlen(message))
	// 	ft_lst_block_add_back(lst_block, ft_lst_block_new(after_quote(&message[tmp], '\''), -1));
	free(boolean);
}
