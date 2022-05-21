/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 17:08:18 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/28 15:48:19 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*check_valid_echo(char *str)
{
	int		i;
	int		len;
	char	*ret;

	ret = NULL;
	len = ft_strlen(str) - 2;
	if (len > 0)
	{
		ret = malloc(len * sizeof(char));
		i = 2;
		while (str[i] != '\0')
		{
			ret[i - 2] = str[i];
			i++;
		}
	}
	return (ret);
}

void	echo_dollar(t_mini *mini, char *cmd)
{
	char	*str;
	char	*check;

	str = ft_itoa(g_check.exit_status);
	ft_putstr_fd(str, mini->glob.fd_red);
	if (mini->glob.fd_red != 1 && mini->cmds.type == PIPE)
		ft_putendl_fd(str, 1);
	check = check_valid_echo(cmd);
	if (check != NULL)
	{
		ft_putstr_fd(check, mini->glob.fd_red);
		if (mini->glob.fd_red != 1 && mini->cmds.type == PIPE)
			ft_putendl_fd(check, 1);
	}
	free(check);
	free(str);
}

void	help_echo(char **cmd, t_mini *mini, int i)
{
	ft_putstr_fd(cmd[i], mini->glob.fd_red);
	if (mini->glob.fd_red != 1 && mini->cmds.type == PIPE)
		ft_putstr_fd(cmd[i], 1);
	if (cmd[i + 1] != NULL)
	{
		ft_putstr_fd(" ", mini->glob.fd_red);
		if (mini->glob.fd_red != 1 && mini->cmds.type == PIPE)
			ft_putstr_fd(" ", 1);
	}
}

void	execute_echo(char **cmd, t_mini *mini)
{
	int		i;
	int		b;

	b = 0;
	i = get_n(cmd, &b);
	while (cmd[i] != NULL)
	{
		help_echo(cmd, mini, i);
		i++;
	}
	if (b == 0)
	{
		ft_putstr_fd("\n", mini->glob.fd_red);
		if (mini->glob.fd_red != 1 && mini->cmds.type == PIPE)
			ft_putstr_fd("\n", 1);
	}
	if (g_check.exit_status == -2)
		g_check.exit_status = 1;
	else
		g_check.exit_status = 0;
}
