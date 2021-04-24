/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 17:08:18 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/22 16:35:01 by amouassi         ###   ########.fr       */
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

int	check_n(char *str)
{
	int	i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	echo_dollar(t_mini *mini, char *cmd)
{
	char	*str;
	char	*check;

	str = ft_itoa(g_check.exit_status);
	ft_putstr_fd(str, mini->glob.fd_red);
	check = check_valid_echo(cmd);
	if (check != NULL)
		ft_putstr_fd(check, mini->glob.fd_red);
	free(check);
	free(str);
}

int	get_n(char **cmd, int *b)
{
	int		i;

	i = 1;
	while (cmd[i] != NULL && (ft_strncmp(cmd[1], "-", 1) == 0
			&& check_n(cmd[i]) == 0))
	{
		*b = 1;
		i++;
	}
	return (i);
}

void	execute_echo(char **cmd, t_mini *mini)
{
	int		i;
	int		b;

	b = 0;
	i = get_n(cmd, &b);
	while (cmd[i] != NULL)
	{
		if (ft_strncmp(cmd[i], "$?", 2) == 0)
			echo_dollar(mini, cmd[i]);
		else
			ft_putstr_fd(cmd[i], mini->glob.fd_red);
		if (cmd[i + 1] != NULL)
			ft_putstr_fd(" ", mini->glob.fd_red);
		i++;
	}
	if (b == 0)
		ft_putstr_fd("\n", mini->glob.fd_red);
	if (g_check.exit_status == -2)
		g_check.exit_status = 1;
	else
		g_check.exit_status = 0;
}
