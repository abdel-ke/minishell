/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 19:36:50 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/17 14:44:23 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_pwd(char *str, int err)
{
	ft_putstr(str);
	ft_putendl_fd(strerror(err), 1);
}

void	error_cd(char *path, int err)
{
	ft_putstr("minishell: cd: ");
	ft_putstr(path);
	ft_putstr(": ");
	ft_putstr(strerror(err));
	ft_putstr("\n");
}

void	error_export(char *str, t_mini *mini)
{
	char	*cmd;

	ft_putstr("minishell: export: `");
	if (ft_strcmp(str, "~") == 0 || ft_strncmp(str, "~/", 2) == 0)
	{
		cmd = search_replace(str, "~", mini->glob.home[1]);
		ft_putstr(cmd);
		free(cmd);
	}
	else if (ft_strcmp(str, "=\"\"") == 0 || ft_strcmp(str, "=\'\'") == 0)
		ft_putstr("=");
	else
		ft_putstr(str);
	ft_putendl_fd("': not a valid identifier", 1);
}

void	error_unset(char *str, t_mini *mini)
{
	char	*cmd;

	ft_putstr("minishell: unset: `");
	if (ft_strcmp(str, "~") == 0 || ft_strncmp(str, "~/", 2) == 0)
	{
		cmd = search_replace(str, "~", mini->glob.home[1]);
		ft_putstr(cmd);
		free(cmd);
	}
	else if (ft_strcmp(str, "=\"\"") == 0 || ft_strcmp(str, "=\'\'") == 0)
		ft_putstr("=");
	else
		ft_putstr(str);
	ft_putendl_fd("': not a valid identifier", 1);
}

void	error_exit(char *str)
{
	ft_putstr("exit\nminishell: exit: ");
	ft_putstr(str);
	ft_putstr(": numeric argument required\n");
}
