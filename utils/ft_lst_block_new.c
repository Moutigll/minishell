/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_block_new.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:51:11 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/16 15:05:24 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_block	*ft_lst_block_new(char *content, int i)
{
	t_block	*new_node;

	new_node = (t_block *) malloc(sizeof(t_block));
	if (new_node == NULL)
		return (NULL);
	new_node->content = content;
	new_node->boolean = i;
	new_node->next = NULL;
	return (new_node);
}
