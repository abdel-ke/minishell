/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:50:59 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/22 16:35:32 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sub_exec_export(t_mini *mini, char *cmd, char **split, char *join)
{
	char	*tmp;

	if (ft_strncmp(cmd, "SHLVL", 5) == 0)
	{
		if (check_in_env(mini->env, split[0]) == 0)
			ft_lstadd_back(&mini->export_env, ft_lstnew(ft_strdup("SHLVL")));
		else
		{
			mod_env(mini->export_env, "SHLVL", join);
			mod_env(mini->env, "SHLVL", join);
		}
	}
	if (ft_strncmp(cmd, "OLDPWD", 6) == 0)
	{
		if (mini->glob.oldpwd != NULL && check_in_env(mini->env, split[0]) == 0)
		{
			tmp = ft_strjoin("OLDPWD=", mini->glob.oldpwd);
			ft_lstadd_back(&mini->env, ft_lstnew(tmp));
		}
		mini->glob.oldpwd_env = 0;
	}
}

void	s_execute_export(t_mini *mini, char **split)
{
	char	*tmp;

	if (mini->glob.oldpwd != NULL
		&& check_in_env(mini->export_env, split[0]) == 0)
	{
		tmp = ft_strjoin("OLDPWD=", mini->glob.oldpwd);
		ft_lstadd_back(&mini->export_env, ft_lstnew(tmp));
	}
	mini->glob.oldpwd_env = 0;
}

void	h_execute_export(t_mini *mini, char **split, char *cmd)
{
	if (check_in_env(mini->export_env, split[0]) == 1 && check_valid(cmd) == 1)
		mod_env(mini->export_env, split[0], cmd);
	else if (check_in_env(mini->export_env, split[0]) != 1)
	{
		if (ft_strncmp(cmd, "PWD", 3) == 0)
			mini->glob.pwd_env = 0;
		ft_lstadd_back(&mini->export_env, ft_lstnew(ft_strdup(cmd)));
	}
}

void	help_execute_export(t_mini *mini, char *cmd)
{
	char	**split;
	char	*lvl;
	char	*join;

	split = ft_split(cmd, '=');
	lvl = ft_itoa(mini->glob.shlvl);
	join = ft_strjoin("SHLVL=", lvl);
	if (ft_strncmp(cmd, "SHLVL", 5) == 0 || ft_strncmp(cmd, "OLDPWD", 6) == 0)
		sub_exec_export(mini, cmd, split, join);
	if (ft_strncmp(cmd, "OLDPWD", 6) == 0 && mini->glob.oldpwd != NULL)
		s_execute_export(mini, split);
	if ((check_in_env(mini->export_env, split[0]) == 1 && check_valid(cmd) == 1)
		|| check_in_env(mini->export_env, split[0]) != 1)
		h_execute_export(mini, split, cmd);
	if (check_in_env(mini->env, split[0]) == 1 && check_valid(cmd) == 1)
		mod_env(mini->env, split[0], cmd);
	else if (check_in_env(mini->env, split[0]) != 1 && check_valid(cmd) == 1)
		ft_lstadd_back(&mini->env, ft_lstnew(ft_strdup(cmd)));
	free_tabl(split);
	free(lvl);
	free(join);
}

void	execute_export(t_mini *mini)
{
	int	i;

	if (g_check.exit_status == -2)
		g_check.exit_status = 1;
	else
		g_check.exit_status = 0;
	i = 1;
	if (mini->cmds.cmd[1] == NULL)
	{
		sort_list(mini->export_env);
		print_export(mini->export_env, mini->glob.fd_red);
	}
	while (mini->cmds.cmd[i] != NULL)
	{
		if (check_syntax_export(mini->cmds.cmd[i]) == 1)
		{
			error_export(mini->cmds.cmd[i], mini);
		}
		else
			help_execute_export(mini, mini->cmds.cmd[i]);
		i++;
	}
}
