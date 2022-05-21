/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 15:12:37 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/26 15:14:47 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	help_cd_home_cur(t_mini *mini)
{
	char	*tmp;
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
	tmp = search_replace(mini->cmds.cmd[1], "~", home[1]);
	check_dir = chdir(tmp);
	if (check_dir == -1)
	{
		error_cd(tmp, errno);
		g_check.exit_status = 1;
	}
	mod_pwd(mini);
	free_tabl(home);
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
