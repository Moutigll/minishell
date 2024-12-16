/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:51:11 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/12 14:52:49 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*ft_lstnew(char	*name_var, char	*content)
{
	t_list	*new_node;

	new_node = (t_list *) malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->name_var = name_var;
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
