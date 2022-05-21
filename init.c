/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:07:05 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/29 16:11:36 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_mini *mini, char **environ)
{
	mini->env = init_env_environ(environ);
	mini->export_env = init_export_environ(environ);
	mini->unset = NULL;
	mini->glob.home = ft_getenv("HOME", mini->env);
	mini->glob.mini_ret = 0;
	mini->glob.b_exit = 0;
	mini->glob.oldpwd = NULL;
	mini->glob.oldpwd_env = 0;
	mini->glob.pwd_env = 0;
	mini->glob.pwd = NULL;
	mini->cmds.cmd = NULL;
	g_check.exit_status = 0;
	mini->history = NULL;
	mini->cmdline = NULL;
}

void	set_terminal(struct termios term)
{
	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, getenv("TERM"));
}
