/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 21:48:59 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/29 11:50:54 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_ctrld(char *cmdline)
{
	if ((cmdline == NULL || (cmdline != NULL && ft_strlen(cmdline) == 0)))
	{
		ft_putstr_fd("exit\n", 1);
		exit(EXIT_SUCCESS);
	}
}

int	termcap(t_termcap *term, char **cmdline)
{
	if (term->buffer[0] == DELETE)
	{
		if (*cmdline != NULL)
		{
			term->c = ft_strlen(*cmdline);
			delete(cmdline, term);
		}
	}
	else if (term->buffer[0] == CTRLD)
		exec_ctrld(*cmdline);
	else if (term->buffer[0] == LEFTRIGHT)
		;
	else if (term->buffer[0] == ENTER)
	{
		if (*cmdline != NULL)
			term->c += ft_strlen(*cmdline);
		return (1);
	}
	return (0);
}

void	help_get_cmdline(t_termcap *term, char **cmdline, char *tmp_save)
{
	char	*tmp;

	tmp = *cmdline;
	*cmdline = ft_strjoin(*cmdline, term->buffer);
	if (*cmdline != NULL)
	{
		term->check = 0;
		tmp_save = term->save;
		term->save = ft_strdup(*cmdline);
		if (tmp_save != NULL)
			free(tmp_save);
	}
	free(tmp);
}

void	get_cmdline(t_termcap *term, char **cmdline)
{
	char	*tmp_save;

	tmp_save = NULL;
	if (*cmdline == NULL)
	{
		*cmdline = ft_strdup(term->buffer);
		if (*cmdline != NULL)
		{
			term->check = 0;
			tmp_save = term->save;
			term->save = ft_strdup(*cmdline);
			if (tmp_save != NULL)
				free(tmp_save);
		}
	}
	else
		help_get_cmdline(term, cmdline, tmp_save);
	term->c += 1;
	ft_putstr_fd(term->buffer, 1);
}
