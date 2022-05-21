/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 21:47:20 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/29 11:46:23 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_termcap(t_termcap *term, t_list **history, char **cmdline)
{
	ioctl(0, TIOCGWINSZ, &term->win);
	term->c = 0;
	term->lstsize = ft_lstsize(*history);
	*cmdline = NULL;
	term->histadd = NULL;
	term->prevlen = 0;
	term->histpos = term->lstsize;
}

void	help_check_buffer(t_termcap *term)
{
	term->check = 1;
	if (ft_strlen(term->save) > 0)
	{
		tputs(tgoto(tgetstr("LE", NULL), 0, ft_strlen(term->save)), 0, fd_put);
		tputs(tgoto(tgetstr("ce", NULL), 0, ft_strlen(term->save)), 0, fd_put);
	}
}

int	check_buffer(t_termcap *term, t_list **history, char **cmdline)
{
	if (!ft_strcmp(term->buffer, UP))
	{
		if (term->save != NULL && term->check == 0)
			help_check_buffer(term);
		uphistory(term, history, cmdline);
	}
	else if (!ft_strcmp(term->buffer, DOWN))
	{
		if (term->save != NULL && term->check == 0)
			help_check_buffer(term);
		downhistory(term, history, cmdline);
	}
	else if (term->buffer[0] == DELETE || term->buffer[0] == CTRLD
		|| term->buffer[0] == LEFTRIGHT || term->buffer[0] == ENTER)
	{
		if (termcap(term, cmdline) == 1)
			return (1);
	}
	else
		get_cmdline(term, cmdline);
	return (0);
}

void	help_readline(char **cmdline, t_termcap	*term)
{
	g_check.exit_status = 1;
	term->prevlen = 0;
	free(term->save);
	term->save = NULL;
	free(*cmdline);
	*cmdline = NULL;
}

void	readline(char **cmdline, t_list **history)
{
	t_termcap	term;

	term.save = NULL;
	term.check = 0;
	init_termcap(&term, history, cmdline);
	while (1)
	{
		term.buffer[0] = '\0';
		term.ret = read(0, term.buffer, 4);
		if (g_check.exit_status == -1)
			help_readline(cmdline, &term);
		term.buffer[term.ret] = '\0';
		if (check_buffer(&term, history, cmdline) == 1)
			break ;
	}
	if (*cmdline != NULL && ft_strlen(*cmdline) != 0)
		ft_lstadd_back(history, ft_lstnew(ft_strdup(*cmdline)));
	if (term.save != NULL)
		free(term.save);
}
