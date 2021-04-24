/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 19:11:18 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/22 12:03:34 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(t_mini *mini)
{
	if (check_isbuiltin(mini->cmds.cmd[0]) == 1
		&& mini->glob.exit_pipe == 0 && mini->cmds.type != PIPE)
	{
		if (mini->glob.exit_pipe == 0)
		{
			execute_builtins(mini);
		}
	}
	else
	{
		if (mini->cmds.type == PIPE)
			mini->glob.exit_pipe = 1;
		execute_shell(mini);
	}
}
