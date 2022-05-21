/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 10:41:28 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/29 00:08:59 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	help_execute_cd_old(t_mini *mini)
{
	if (mini->glob.oldpwd != NULL)
		free(mini->glob.oldpwd);
	mini->glob.oldpwd = NULL;
	mini->glob.pwd_env = 0;
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
	if (mini->glob.pwd_env == 1)
		help_execute_cd_old(mini);
}

void	help_execute_cd(t_mini *mini)
{
	char	*save_oldpwd;
	char	cwd[PATH_MAX];

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
	if (getcwd(cwd, PATH_MAX) == NULL)
		current_dir_err();
	mod_pwd(mini);
	if (save_oldpwd != NULL)
		free(save_oldpwd);
}

void	cd_home(t_mini *mini)
{
	int		check_dir;
	char	**home;

	home = ft_getenv("HOME", mini->export_env);
	if (home == NULL)
	{
		ft_putstr("minishell : cd: HOME not set\n");
		g_check.exit_status = 1;
		return ;
	}
	mod_oldpwd(mini);
	check_dir = chdir(home[1]);
	if (check_dir == -1)
	{
		error_cd(home[1], errno);
		g_check.exit_status = 1;
	}
	mod_pwd(mini);
	free_tabl(home);
}

void	execute_cd(t_mini *mini)
{
	char	*tmp_path;

	if (g_check.exit_status == -2)
		g_check.exit_status = 1;
	else
		g_check.exit_status = 0;
	tmp_path = NULL;
	if (mini->cmds.cmd[1] == NULL)
		cd_home(mini);
	else if (ft_strncmp(mini->cmds.cmd[1], "~", 1) == 0
		|| ft_strcmp(mini->cmds.cmd[1], ".") == 0)
		 execute_cd_home_cur(mini);
	else if (ft_strcmp(mini->cmds.cmd[1], "-") == 0)
		execute_cd_old(mini);
	else
		help_execute_cd(mini);
	free(tmp_path);
}
