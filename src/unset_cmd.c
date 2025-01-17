/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:07:29 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/17 12:02:19 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	unset_cmd(t_head *head, t_main **main)
{
	t_head	*head_tmp;
	char	*result;
	int		tab;
	int		tmp;
	int		n;

	tmp = check_equal("unset", head, 0);
	n = tmp;
	if (tmp >= 0)
	{
		while (n != -1 && *main)
		{
			head_tmp = return_head(head, tmp);
			tmp += find_block(head_tmp, &n, &result, 1) - 1;
			free(head_tmp);
			tab = search_env(*main, result);
			free(result);
			if (tab != -1)
				(*main)->g_env = ft_realoc_ptr_unset((*main)->g_env, tab);
		}
		return (1);
	}
	return (0);
}
