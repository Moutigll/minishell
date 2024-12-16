/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:23:14 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/16 13:18:00 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*remove_double_quote(char *content)
{
	char	*result;
	int		size;
	int		i;

	i = 1;
	size = ft_strlen(content) - 1;
	result = malloc(sizeof(char) * (ft_strlen(content) - 1));
	while (content[i] && i < size)
	{
		result[i - 1] = content[i];
		i++;
	}
	result[i - 1] = '\0';
	free(content);
	return (result);
}

void	change_direct(char *name_var, char *content)
{
	char	*result;
	int		tab;
	int		i;
	int		j;

	j = 0;
	i = 0;
	tab = search_exist(name_var);
	result = malloc(sizeof(char) * (ft_strlen(name_var) + ft_strlen(content) + 2));
	while (name_var[i])
	{
		result[i] = name_var[i];
		i++;
	}
	result[i++] = '=';
	while (content[j])
	{
		result[i + j] = content[j];
		j++;
	}
	result[i + j] = '\0';
	free(g_env[tab]);
	g_env[tab] = result;
}

void	replace_var_lst(t_list **lst_var, char *content, int tab)
{
	t_list	*node_var;
	t_list	*temp_node;
	t_list	*prev;

	node_var = lst_returnn(*lst_var, tab);
	if (node_var == NULL)
		return;
	temp_node = ft_lstnew(node_var->name_var, content);
	if (!temp_node)
		return;
	temp_node->next = node_var->next;
	if (node_var == *lst_var)
		*lst_var = temp_node;
	else
	{
		prev = *lst_var;
		while (prev != NULL && prev->next != node_var)
			prev = prev->next;
		if (prev != NULL)
			prev->next = temp_node;
	}
}
