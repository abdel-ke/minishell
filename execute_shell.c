/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:46:29 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/23 12:05:59 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_execve(t_mini *mini, char **env, char **split)
{
	char	*path;
	int		perm;

	path = NULL;
	get_path(mini, split, &path, &perm);
	call_execve(mini, env, path);
	if (perm != 1 && mini->cmds.cmd[0] != NULL
		&& check_isbuiltin(mini->cmds.cmd[0]) != 1
		&& g_check.exit_status != -2)
	{
		g_check.exit_status = 127;
		error_command(mini->cmds.cmd[0]);
	}
	if (g_check.exit_status == -2)
		g_check.exit_status = 1;
	if (path != NULL)
		free(path);
}

void	execute_path(t_mini *mini, char **env)
{
	int		permission;
	char	*path;

	path = ft_strdup(mini->cmds.cmd[0]);
	permission = check_permission(path);
	if (permission == 1)
		call_execve(mini, env, path);
	else
	{
		if (permission == 2)
		{
			g_check.exit_status = 126;
			error_permission(mini->cmds.cmd[0]);
		}
		else if (permission == 3)
		{
			g_check.exit_status = 127;
			error_nodir(mini->cmds.cmd[0]);
		}
	}
	free(path);
}

void	check_cur_exec(t_mini *mini, char **env)
{
	char	*path;
	char	*join;
	char	cwd[PATH_MAX];
	int		permission;

	getcwd(cwd, PATH_MAX);
	join = ft_strjoin(cwd, "/");
	path = ft_strjoin(join, mini->cmds.cmd[0]);
	permission = check_permission(path);
	if (permission == 1 || check_pipe_builtins(mini) == 1)
		call_execve(mini, env, path);
	else if (check_pipe_builtins(mini) != 1)
	{
		if (permission == 2)
			error_permission(mini->cmds.cmd[0]);
		else if (permission == 3)
		{
			error_nodir(mini->cmds.cmd[0]);
		}
	}
	free(join);
	free(path);
}

void	execute_shell(t_mini *mini)
{
	char	**split;
	char	**env_path;

	g_check.exit_status = 0;
	mini->glob.env_tab = list_to_tabl(mini->env);
	env_path = ft_getenv("PATH", mini->env);
	if (mini->cmds.cmd[0] != NULL
		&& (ft_strncmp(mini->cmds.cmd[0], "./", 2) == 0
			|| mini->cmds.cmd[0][0] == '/'))
		execute_path(mini, mini->glob.env_tab);
	else if (env_path == NULL)
		check_cur_exec(mini, mini->glob.env_tab);
	if (env_path != NULL)
	{
		free_tabl(env_path);
		env_path = ft_getenv("PATH", mini->env);
		split = ft_split(env_path[1], ':');
		execute_execve(mini, mini->glob.env_tab, split);
		free_tabl(split);
	}
	free_tabl(mini->glob.env_tab);
	if (env_path != NULL)
		free_tabl(env_path);
}
