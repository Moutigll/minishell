/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 13:00:56 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/15 13:02:43 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	change_var(int n, t_node **node, char *new_char, int z, int p)
{
	char	*result;
	int		i = 0; // Index pour parcourir la chaîne originale
	int		j = 0; // Index pour parcourir new_char
	int		k;     // Index pour parcourir le reste de la chaîne originale après remplacement

	// Allocation de mémoire pour le résultat final
	result = malloc(sizeof(char) * (n + 1));
	if (!result)
		return; // Gérer une éventuelle erreur d'allocation

	// Copie de la partie de la chaîne avant le '$'
	while ((*node)->content[i] && (*node)->content[i] != '$')
	{
		result[i] = (*node)->content[i];
		i++;
	}

	// Sauter la partie à remplacer (z caractères après '$')
	k = i + z;

	// Ajout de la nouvelle chaîne
	while (new_char[j])
	{
		result[i] = new_char[j];
		i++;
		j++;
	}

	// Si la taille de remplacement (p) est plus grande que z, ajuster k
	if (j < p)
		k += (p - z);

	// Copie de la partie restante de la chaîne originale
	while ((*node)->content[k])
	{
		result[i] = (*node)->content[k];
		i++;
		k++;
	}

	// Terminer la nouvelle chaîne avec '\0'
	result[i] = '\0';

	// Libérer l'ancienne chaîne et remplacer par le résultat
	free((*node)->content);
	(*node)->content = result;
}

char	*return_name_var(char *content, char c)
{
	char	*result;
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (content[i] && content[i] != ' ' && content[i] != c && content[i] != '\'')
		i++;
	result = malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		result[j] = content[j];
		j++;
	}
	result[j] = '\0';
	return (result);
}

static int	remove_equal(char *content)
{
	int	i;

	i = 0;
	while (content[i] != '=')
		i++;
	return (i + 1);
}

static char	*return_var_local(t_list *lst, char *name_var)
{
	while (lst)
	{
		if (ft_strcmp((const char *)return_before(lst->content), (const char *)&name_var[1]) == 0)
			return (lst->content);
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (NULL);
}

static void	return_var(t_node **node, char **g_env, t_list *lst)
{
	char	*name_var;
	int		tab;
	int		i;

	i = 0;
	while ((*node)->content[i])
	{
		if ((*node)->content[i] == '$')
		{
			name_var = return_name_var(&(*node)->content[i], '$');
			tab = search_exist(&name_var[1], g_env);
			if (return_var_local(lst, name_var) == NULL)
			{
				if (tab >= 0)
				{
					change_var((int)ft_strlen((const char *)(*node)->content) - (int)ft_strlen((const char *)name_var) + (int)ft_strlen((const char *)&g_env[tab][remove_equal(g_env[tab])]) + 1,
						node, &g_env[tab][remove_equal(g_env[tab])], (int)ft_strlen((const char *)name_var), (int)ft_strlen((const char *)name_var));
					i += (int)ft_strlen((const char *)&g_env[tab][remove_equal(g_env[tab])]);
				}
				else
				{
					change_var((int)ft_strlen((const char *)(*node)->content) - (int)ft_strlen((const char *)name_var) + 1,
						node, "", 0, (int)ft_strlen((const char *)name_var));
					if (ft_strlen((*node)->content) == 0)
						(*node)->head = -1;
				}
			}
			else
			{
				change_var((int)ft_strlen((const char *)(*node)->content) - (int)ft_strlen((const char *)name_var) + (int)ft_strlen((const char *)&return_var_local(lst, name_var)[remove_equal(return_var_local(lst, name_var))]) + 1,
						node, &return_var_local(lst, name_var)[remove_equal(return_var_local(lst, name_var))], (int)ft_strlen((const char *)name_var), (int)ft_strlen((const char *)name_var));
				i += (int)ft_strlen((const char *)&return_var_local(lst, name_var)[remove_equal(return_var_local(lst, name_var))]);
			}
			free(name_var);
		}
		else
			i++;
	}
}

int	search_exist(char *name_var, char **g_env)
{
	int	i;
	int	j;

	i = 0;
	while (g_env[i])
	{
		j = 0;
		while (g_env[i][j] && g_env[i][j] == name_var[j] && g_env[i][j] != '=')
			j++;
		if (j == (int)ft_strlen(name_var))
			return (i);
		i++;
	}
	return (-1);
}

void replace_var(t_head **head, t_main *main)
{
	t_node	*node;
	t_list	*lst;

	lst = (*head)->head;
	while (lst)
	{
		node = lst->content;
		if (node->type != 1)
			return_var(&node, main->g_env, main->lst_var);
		lst = lst->next;
	}
}
