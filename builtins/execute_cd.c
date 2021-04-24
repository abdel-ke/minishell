/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 10:41:28 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/22 16:34:20 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	help_cd_home_cur(t_mini *mini)
{
	char	*tmp;
	int		check_dir;

	mod_oldpwd(mini);
	tmp = search_replace(mini->cmds.cmd[1], "~", mini->glob.home[1]);
	check_dir = chdir(tmp);
	if (check_dir == -1)
	{
		error_cd(tmp, errno);
		g_check.exit_status = 1;
	}
	mod_pwd(mini);
	free(tmp);
}

void	execute_cd_home_cur(t_mini *mini)
{
	char	cwd[PATH_MAX];

	if (ft_strncmp(mini->cmds.cmd[1], "~", 1) == 0)
		help_cd_home_cur(mini);
	else if (ft_strcmp(mini->cmds.cmd[1], ".") == 0)
	{
		mod_oldpwd(mini);
		if (getcwd(cwd, PATH_MAX) == NULL)
			current_dir_err();
		else
		{
			if (mini->glob.oldpwd != NULL)
				free(mini->glob.oldpwd);
			mini->glob.oldpwd = ft_strdup(cwd);
			mod_pwd(mini);
		}
	}
}

void	execute_cd_old(t_mini *mini)
{
	char	cwd[PATH_MAX];

	if (mini->glob.oldpwd == NULL)
	{
		ft_putstr("minishell : cd: OLDPWD not set\n");
		g_check.exit_status = 1;
	}
	else
	{
		getcwd(cwd, PATH_MAX);
		if (chdir(mini->glob.oldpwd) == -1)
		{
			error_cd(mini->glob.oldpwd, errno);
			g_check.exit_status = 1;
			return ;
		}
		ft_putendl_fd(mini->glob.oldpwd, 1);
		if (mini->glob.oldpwd != NULL)
			free(mini->glob.oldpwd);
		mini->glob.oldpwd = ft_strdup(cwd);
		mod_old(mini, ft_strdup(cwd));
	}
}

void	help_execute_cd(t_mini *mini)
{
	char	*save_oldpwd;

	save_oldpwd = NULL;
	if (mini->glob.oldpwd)
		save_oldpwd = ft_strdup(mini->glob.oldpwd);
	mod_oldpwd(mini);
	if (chdir(mini->cmds.cmd[1]) == -1)
	{
		error_cd(mini->cmds.cmd[1], errno);
		reset_oldpwd(mini, save_oldpwd);
		g_check.exit_status = 1;
	}
	mod_pwd(mini);
	if (save_oldpwd != NULL)
		free(save_oldpwd);
}

void	execute_cd(t_mini *mini)
{
	char	*tmp_path;
	int		check_dir;

	if (g_check.exit_status == -2)
		g_check.exit_status = 1;
	else
		g_check.exit_status = 0;
	tmp_path = NULL;
	if (mini->cmds.cmd[1] == NULL)
	{
		mod_oldpwd(mini);
		check_dir = chdir(mini->glob.home[1]);
		mod_pwd(mini);
	}
	else if (ft_strncmp(mini->cmds.cmd[1], "~", 1) == 0
		|| ft_strcmp(mini->cmds.cmd[1], ".") == 0)
		 execute_cd_home_cur(mini);
	else if (ft_strcmp(mini->cmds.cmd[1], "-") == 0)
		execute_cd_old(mini);
	else
		help_execute_cd(mini);
	free(tmp_path);
}
