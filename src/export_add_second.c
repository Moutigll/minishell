/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exprot_add_second.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:25:15 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/27 20:26:29 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_first_char(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

char	*return_value(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] != '\0')
		return (ft_strdup(&str[i + 1]));
	return (NULL);
}

char	*return_key(char *str)
{
	char	*result;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	result = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] && str[i] != '=')
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

t_env_var	*new_var(char *str, char *key, char *value, int exported)
{
	t_env_var	*tmp;

	tmp = malloc(sizeof(t_env_var));
	if (!tmp)
		return (NULL);
	tmp->exported = exported;
	tmp->name = key;
	tmp->value = value;
	return (tmp);
}
