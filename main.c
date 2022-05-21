/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 21:28:51 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/30 00:36:32 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_terminal(struct termios term)
{
	tcgetattr(0, &term);
	term.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, TCSANOW, &term);
}

int	main(void)
{
	extern char	**environ;
	t_mini		mini;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	init(&mini, environ);
	shlvl(&mini);
	initail_struct(&mini);
	while (1)
	{
		set_terminal(mini.term);
		ft_putstr("\033[33mminishell\033[0m\033[32m~$\033[0m ");
		readline(&mini.cmdline, &mini.history);
		ft_putchar_fd('\n', 1);
		unset_terminal(mini.term);
		if (mini.cmdline != NULL)
		{
			if (minishell(&mini) == 1)
				break ;
		}
		sub_free_mini(&mini);
	}
	free_mini(&mini);
	return (mini.glob.mini_ret);
}
