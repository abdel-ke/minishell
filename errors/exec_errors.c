/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 16:43:14 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/23 12:08:16 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_command(char *command)
{
	ft_putstr("minishell: ");
	ft_putstr(command);
	ft_putstr(": command not found\n");
}

void	error_permission(char *command)
{
	ft_putstr("minishell: ");
	ft_putstr(command);
	ft_putstr(": Permission denied\n");
}

void	error_nodir(char *command)
{
	ft_putstr("minishell: ");
	ft_putstr(command);
	if (command[0] == '$')
		ft_putstr(": ambiguous redirect\n");
	else
		ft_putstr(": No such file or directory\n");
}

void	current_dir_err(void)
{
	ft_putstr_fd("cd: error retrieving current directory:", 1);
	ft_putstr_fd(" getcwd: cannot access parent directories:", 1);
	ft_putendl_fd(" No such file or directory", 1);
}
