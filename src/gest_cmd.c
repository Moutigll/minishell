/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:31:00 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/16 11:57:37 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_equal(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str1[i] == str2[i])
		i++;
	if (ft_strlen(str1) == i && (str2[i] == '\0' || str2[i] == ' '))
		return (1);
	return (0);
}

static int	check_var_type(char *command)
{
	int	i;

	i = 0;
	while ((command[i] >= 'a' && command[i] <= 'z') || (command[i] >= 'A' && command[i] <= 'Z'))
		i++;
	if (command[i++] != '=')
		return (0);
	if (command[i] == '"' && command[ft_strlen(command) - 1] == '"')
		return (1);
	while (command[i] && command[i] != ' ')
		i++;
	if (command[i] == '\0')
		return (1);
	return (0);
}

static void	add_var(t_list **lst_var, char *command)
{
	char	*name_var;
	char	*content;
	int		tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (command[i] != '=')
		i++;
	name_var = get_name_var(command);
	content = malloc(sizeof(char) * (ft_strlen(command) - ft_strlen(name_var) + 1));
	while (command[++i])
	{
		content[j] = command[i];
		j++;
	}
	content[j] = '\0';
	if (search_exist(name_var) != -1)
	{
		change_direct(name_var, content);
		return ;
	}
	tab = lst_look_word(*lst_var, name_var);
	if (tab == -1)
		ft_lstadd_back(lst_var, ft_lstnew(name_var, content));
	else
		replace_var_lst(lst_var, content, tab);
}

static void	print(t_list *lst_var, char *last_cmd)
{
	printf("%s\n", last_cmd);
	while (lst_var)
	{
		printf("%s=%s\n", lst_var->name_var, lst_var->content);
		if (!lst_var->next)
			break ;
		lst_var = lst_var->next;
	}
}

void	cmd_format(char *command, t_list **lst_var, char *last_cmd)
{
	int	i;

	i = 0;
	while_space(command, &i);
	if (command[0] != '\0')
		last_cmd = ft_last_cmd(last_cmd, command);
	if (check_equal("exit", &command[i]))
	{
		ft_lstclear(lst_var);
		free_env();
		free(command);
		printf("exit\n");
		exit(0);
	}
	else if (check_equal("echo", &command[i]))
		echo_cmd(&command[i], lst_var);
	else if (check_equal("pwd", &command[i]))
		pwd_cmd();
	else if (check_equal("cd", &command[i]))
		cd_cmd(&command[i]);
	else if (check_equal("env", &command[i]))
		print_env();
	else if (check_equal("export", &command[i]))
		export_cmd(&command[i], lst_var);
	else if (check_equal("unset", &command[i]))
		unset_cmd(&command[i]);
	else if (check_equal("look", &command[i]))
		print(*lst_var, last_cmd);
	else if (check_var_type(&command[i]))
		add_var(lst_var, &command[i]);
	else if (command[0] != '\0')
		printf("%s: command not found\n", &command[i]);
	free(command);
}
