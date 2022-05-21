/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 21:27:11 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/26 12:51:27 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT && g_check.exit_sig == 0)
	{
		g_check.exit_status = -1;
		ft_putstr("\n\033[33mminishell\033[0m\033[32m~$\033[0m ");
	}
	if (sig == SIGQUIT && g_check.exit_sig == 0)
		;
}

void	child_sig_handler(int status)
{
	if (WIFEXITED(status))
		g_check.exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
		{
			g_check.exit_status = 130;
			ft_putchar_fd('\n', 1);
		}
		if (WTERMSIG(status) == 3)
		{
			g_check.exit_status = 131;
			ft_putendl_fd("Quit: 3", 1);
		}
	}
}
