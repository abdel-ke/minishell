/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 11:16:31 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/29 16:26:27 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	help_unset(t_mini *mini, int i)
{
	if (ft_strncmp(mini->cmds.cmd[i], "OLDPWD", 6) == 0)
	{
		if (mini->glob.oldpwd != NULL)
			free(mini->glob.oldpwd);
		mini->glob.oldpwd = NULL;
		mini->glob.oldpwd_env = 1;
	}
	if (ft_strncmp(mini->cmds.cmd[i], "PWD", 3) == 0)
		mini->glob.pwd_env = 1;
	if (check_syntax_unset(mini->cmds.cmd[i]) == 1)
		error_unset(mini->cmds.cmd[i], mini);
	else
	{
		unset_env(mini->cmds.cmd[i], &mini->env);
		unset_env(mini->cmds.cmd[i], &mini->export_env);
	}
}

void	execute_unset(t_mini *mini)
{
	int	i;

	if (g_check.exit_status == -2)
		g_check.exit_status = 1;
	else
		g_check.exit_status = 0;
	i = 1;
	if (mini->cmds.cmd[1] == NULL)
		return ;
	while (mini->cmds.cmd[i] != NULL)
	{
		help_unset(mini, i);
		i++;
	}
}
