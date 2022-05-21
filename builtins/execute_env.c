/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:48:36 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/28 00:39:30 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	help_env(t_mini *mini)
{
	if (ft_strcmp(mini->cmds.cmd[1], "=") == 0
		|| ft_strcmp(mini->cmds.cmd[1], "==") == 0)
	{
		printf("env: setenv %s: Invalid argument\n", mini->cmds.cmd[1]);
		g_check.exit_status = 1;
	}
	else
	{
		ft_putstr_fd("env: ", 0);
		ft_putstr_fd(mini->cmds.cmd[1], 0);
		ft_putendl_fd(": No such file or directory", 1);
		g_check.exit_status = 127;
	}
}

void	execute_env(t_mini *mini)
{
	if (g_check.exit_status == -2)
		g_check.exit_status = 1;
	else
		g_check.exit_status = 0;
	if (mini->cmds.cmd[1] != NULL && ft_strcmp(mini->cmds.cmd[1], "#") != 0)
		help_env(mini);
	else
	{
		print_list(mini->env, mini->glob.fd_red);
		ft_putendl_fd("_=/usr/bin/env", mini->glob.fd_red);
		if (mini->glob.fd_red != 1 && mini->cmds.type == PIPE)
		{
			print_list(mini->env, 1);
			ft_putendl_fd("_=/usr/bin/env", 1);
		}
	}
}
