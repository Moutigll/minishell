/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:59:42 by tle-goff          #+#    #+#             */
/*   Updated: 2025/02/10 21:37:20 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	change_pwd_var(t_env_var	*var, char **envp, int i, int len)
{
	char	*result;
	char	*tmp;

	if (ft_strcmp(var->value, &envp[i][len + 1]) != 0)
	{
		tmp = ft_strjoin(var->name, "=");
		if (!tmp)
			return (MALLOC_ERROR);
		result = ft_strjoin(tmp, var->value);
		if (!result)
			return (free(tmp), MALLOC_ERROR);
		free(tmp);
		free(envp[i]);
		envp[i] = result;
	}
	return (0);
}

int	change_pwd(t_list *lst, char **envp)
{
	t_env_var	*var;
	int			len;
	int			i;

	while (lst)
	{
		i = 0;
		var = lst->content;
		len = ft_strlen(var->name);
		while (envp[i])
		{
			if (ft_strncmp(var->name, envp[i], len) == 0
				&& envp[i][len] == '=')
			{
				if (change_pwd_var(var, envp, i, len) != 0)
					return (MALLOC_ERROR);
			}
			i++;
		}
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (0);
}

int	check_redirect_n(char *str, char c, char vs, int *redirect)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (str[i] == '\0' && *redirect == 1)
		return (1);
	while (str[i])
	{
		if (str[i] == '(' || str[i] == ')' || str[i] == '[' || str[i] == ']')
			return (1);
		else if (str[i] == c && count > 1)
			return (1);
		else if (str[i] == c && count <= 1)
			count++;
		else if (str[i] == vs && count > 0)
			return (1);
		else if (str[i] == '|' && count > 0)
			return (1);
		else
			count = 0;
		i++;
	}
	set_redirect(redirect, count);
	return (0);
}

void	count_redirect(char *str)
{
	int		count;
	int		i;
	char	c;

	i = 0;
	count = 0;
	c = str[i];
	if (c != '>' && c != '<')
		return ;
	while (str[i])
	{
		if (count == 2)
			break ;
		if (str[i] == c)
		{
			ft_putchar_fd(c, 2);
			count++;
		}
		i++;
	}
	ft_putstr_fd("'\n", 2);
}

int	change_redirect(int *state, char *str)
{
	int	i;
	int	j;

	j = 0;
	while (str[j] && str[j] != '>' && str[j] != '<'
		&& str[j] != ' ' && str[j] != '\t' && str[j] != '|')
		j++;
	if ((str[j] == '>' || str[j] == '<' || str[j] == '|') && *state == 1)
		return (ft_putstr_fd("minicoquille: ", 2), ft_putstr_fd("\
syntax error near unexpected token `", 2), count_redirect(str), 1);
	i = (int)ft_strlen(str);
	if (i > 0)
		i--;
	while (i >= 0 && str[i])
	{
		if (str[i] != '>' && str[i] != '<' && str[i] != ' ' && str[i] != '\t')
			return (*state = 0, 0);
		if (str[i] == '>' || str[i] == '<')
			return (*state = 1, 0);
		i--;
	}
	return (0);
}
