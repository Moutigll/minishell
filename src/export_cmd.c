/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:10:25 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/16 16:43:18 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_head	*return_head(t_head *head, int i)
{
	t_head	*new_head;
	t_list	*lst;

	lst = return_lst(head, i);
	new_head = malloc(sizeof(t_head));
	new_head->head = lst;
	new_head->size = head->size;
	return (new_head);
}

t_list	*return_lst(t_head *head, int i)
{
	t_list	*lst;
	int		n;

	n = 0;
	lst = head->head;
	while (lst && i > n)
	{
		if (!lst->next)
			break ;
		lst = lst->next;
		n++;
	}
	return (lst);
}

int	find_block(t_head *head, int *n, char **content_block, int boolean)
{
	t_node	*node;
	t_list	*lst;
	int		i;

	i = 0;
	if (!head->head)
		return (*n = -1, -1);
	*content_block = "\0";
	lst = head->head;
	while (lst)
	{
		i++;
		node = lst->content;
		if (i - 1 != 0 && node->head == 1)
			return (i);
		if (boolean == 1)
			*content_block = ft_strjoin((const char *)*content_block, (const char *)node->content);
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (*n = -1, -1);
}

static char	*search_lst_var(t_list *lst, char *key)
{
	while (lst)
	{
		if (ft_strcmp((const char *)return_before(lst->content), (const char *)key) == 0)
			return (lst->content);
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (NULL);
}

static void remove_last_element(t_list **lst)
{
	t_list *current;
    t_list *prev;

    if (!lst || !*lst) // Si la liste est vide
        return;

    current = *lst;

    // Si la liste ne contient qu'un seul élément
    if (!current->next)
    {
        free(current);
        *lst = NULL;
        return;
    }

    // Parcourir la liste jusqu'à l'avant-dernier élément
    while (current->next)
    {
        prev = current;
        current = current->next;
    }

    // Supprimer le dernier élément
    free(current);
    prev->next = NULL;
}

static t_list *remove_node_by_content(t_list *lst, char *str)
{
    t_list *current;
    t_list *prev;

    if (!lst || !str)
        return lst;

    current = lst;
    prev = NULL;

    while (current)
    {
        // Si le contenu du nœud correspond à `str`
        if (ft_strcmp((const char *)current->content, (const char *)str) == 0)
        {
            if (prev == NULL) // Si le nœud à supprimer est le premier
            {
                t_list *next_node = current->next;
                free(current->content); // Libérer le contenu si alloué dynamiquement
                free(current);          // Libérer le nœud lui-même
                return next_node;       // Retourner le nouveau début de la liste
            }
            else // Si le nœud à supprimer est au milieu ou à la fin
            {
                prev->next = current->next;
                free(current->content); // Libérer le contenu si alloué dynamiquement
                free(current);          // Libérer le nœud lui-même
                return lst;             // La tête de la liste ne change pas
            }
        }
        prev = current;
        current = current->next;
    }
    return lst; // Retourne la liste si aucun nœud n'a été supprimé
}

int	export_cmd(t_head *head, t_main **main)
{
	t_head	*node;
	int		result;
	char	*content_tmp;
	int		tmp;
	int		n;
	int		i;


	tmp = check_equal("export", head, 0);
	n = tmp;
	i = n;
	if (tmp >= 0)
	{
		tmp = 0;
		while (n != -1)
		{
			node = return_head(head, i);
			find_block(node, &n, &content_tmp, 1);
			result = verif_var(node, main, 1);

			if (result == 0)
			{
				remove_last_element(&(*main)->lst_var);
				(*main)->g_env = ft_realoc_ptr((*main)->g_env, content_tmp);
			}
			else if (result != -10)
			{
				if (search_env(*main, content_tmp) == -1)
				{
					(*main)->g_env = ft_realoc_ptr((*main)->g_env, search_lst_var((*main)->lst_var, content_tmp));
					(*main)->lst_var = remove_node_by_content((*main)->lst_var, search_lst_var((*main)->lst_var, content_tmp));
				}
			}
			i += find_block(node, &n, &content_tmp, 0) - 1;
			free(node);
			tmp++;
		}
		return (1);
	}
	return (0);
}
