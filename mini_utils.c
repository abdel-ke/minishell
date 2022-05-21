/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 13:49:56 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/29 15:30:05 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_help_main(t_mini *mini, char **env)
{
	if (mini->cmds.file != NULL)
	{
		cf_lstclear(&mini->cmds.file, free);
		mini->cmds.file = NULL;
	}
	if (mini->cmds.cmd != NULL)
	{
		free_tabl(mini->cmds.cmd);
		mini->cmds.cmd = NULL;
	}
	free_tabl(env);
	env_lstclear(&mini->env2, free);
}

void	help_main(t_mini *mini, t_cflist *tmp)
{
	char	**env;

	mini->cmds.file = NULL;
	g_check.exit_sig = 1;
	mini->cmds.type = tmp->type;
	env = list_to_tabl(mini->export_env);
	mini->env2 = create_env_list(env);
	tmp->name = check_dollr(mini, tmp->name);
	push_to_struct(mini, tmp->name);
	execute_cmd(mini);
	free(mini->under_score);
	mini->under_score = ft_strdup(mini->scmd->name);
	g_check.exit_sig = 0;
	free_help_main(mini, env);
}

void	sub_free_mini(t_mini *mini)
{
	if (mini->cmdline != NULL)
		free(mini->cmdline);
	if (mini->scmd != NULL)
	{
		cf_lstclear(&mini->scmd, free);
		mini->scmd = NULL;
	}
}

int	minishell(t_mini *mini)
{
	mini->tmpline = mini->cmdline;
	mini->cmdline = partition_stage(mini->smbl, mini->cmdline);
	free(mini->tmpline);
	if (!mini->smbl->error)
		splitpipesemi(mini);
	mini->tmp = mini->scmd;
	mini->glob.fd_prv = -1;
	while (mini->tmp != NULL)
	{
		help_main(mini, mini->tmp);
		mini->tmp = mini->tmp->next;
	}
	if (mini->glob.b_exit == 1)
	{
		if (mini->cmdline != NULL)
			free(mini->cmdline);
		return (1);
	}
	return (0);
}
