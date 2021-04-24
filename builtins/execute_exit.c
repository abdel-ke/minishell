/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 13:33:48 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/22 16:38:12 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	help_execute_exit(t_mini *mini)
{
	long long	status;

	status = ft_atoi(mini->cmds.cmd[1]);
	if (status > 255)
	{
		g_check.exit_status = status % 256;
		mini->glob.mini_ret = status % 256;
	}
	else
	{
		if (status == -1)
			error_exit(mini->cmds.cmd[1]);
		g_check.exit_status = status;
		mini->glob.mini_ret = status;
	}
	ft_putstr("exit\n");
	mini->glob.b_exit = 1;
}

void	help_exec_exit(t_mini *mini)
{
	if (check_isnumeriq(mini->cmds.cmd[1]) == 0
		&& mini->cmds.cmd[2] == NULL)
		help_execute_exit(mini);
	else
	{
		if (check_isnumeriq(mini->cmds.cmd[1]) == 0
			&& mini->cmds.cmd[2] != NULL)
			ft_putstr("exit\nminishell: exit: too many arguments\n");
		else
		{
			g_check.exit_status = 255;
			mini->glob.mini_ret = 255;
			error_exit(mini->cmds.cmd[1]);
			mini->glob.b_exit = 1;
		}
	}
}

void	execute_exit(t_mini *mini)
{
	if (g_check.exit_status == -2)
	{
		g_check.exit_status = 1;
		return ;
	}
	else
		g_check.exit_status = 0;
	if (mini->cmds.cmd[1] == NULL)
	{
		g_check.exit_status = 0;
		mini->glob.mini_ret = 0;
		ft_putstr("exit\n");
		mini->glob.b_exit = 1;
	}
	else
		help_exec_exit(mini);
}
