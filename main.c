/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 21:28:51 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/24 13:49:26 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	extern char	**environ;
	t_mini		mini;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	init(&mini, environ);
	shlvl(&mini);
	set_terminal(mini.term);
	initail_struct(&mini);
	while (1)
	{
		ft_putstr("\033[33mminishell\033[0m\033[32m~$\033[0m ");
		readline(&mini.cmdline, &mini.history);
		ft_putchar_fd('\n', 1);
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
