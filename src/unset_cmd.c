/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:07:29 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/08 16:55:15 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	unset_cmd(t_head *head, t_main **main)
{
	char	*result;
	int		tmp;
	int		n;
	int		tab;

	tmp = check_equal("unset", head, 0);
	n = tmp;
	if (tmp >= 0)
	{
		while (n != -1 && *main)
		{
			tmp += find_block(return_head(head, tmp), &n, &result, 1) - 1;
			tab = search_env(*main, result);
			if (tab != -1)
				(*main)->g_env = ft_realoc_ptr_unset((*main)->g_env, tab);
		}
		return (1);
	}
	return (0);
}
