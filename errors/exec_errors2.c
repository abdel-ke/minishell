/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:05:32 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/26 14:07:01 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_nodir(char *command)
{
	ft_putstr("minishell: ");
	ft_putstr(command);
	ft_putstr(": No such file or directory\n");
}

void	current_dir_err(void)
{
	ft_putstr_fd("cd: error retrieving current directory:", 1);
	ft_putstr_fd(" getcwd: cannot access parent directories:", 1);
	ft_putendl_fd(" No such file or directory", 1);
}

void	error_dir(char *command)
{
	ft_putstr("minishell: ");
	ft_putstr(command);
	ft_putstr(": Is a directory\n");
}
