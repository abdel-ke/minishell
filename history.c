/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 12:39:58 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/28 16:46:32 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	uphistory(t_termcap *term, t_list **history, char **cmdline)
{
	char	**hist_tab;

	if (term->lstsize != 0)
	{
		if (term->prevlen != 0)
		{
			tputs(tgoto(tgetstr("cr", NULL), 0, term->prevlen), 0, fd_put);
			tputs(tgoto(tgetstr("ce", NULL), 0, term->prevlen), 0, fd_put);
			ft_putstr("\033[33mminishell\033[0m\033[32m~$\033[0m ");
		}
		hist_tab = list_to_tabl(*history);
		if (term->histpos != 0)
			term->histpos -=1;
		ft_putstr_fd(hist_tab[term->histpos], 1);
		term->prevlen = ft_strlen(hist_tab[term->histpos]);
		if (*cmdline != NULL)
			free(*cmdline);
		if (hist_tab[term->histpos] != NULL)
		{
			*cmdline = ft_strdup(hist_tab[term->histpos]);
			term->c = ft_strlen(*cmdline);
		}
		free_tabl(hist_tab);
	}
}

void	delete_dhist(t_termcap *term, char **cmdline)
{
	if ((term->prevlen != 0 && term->histpos != term->lstsize)
		|| (term->prevlen != 0 && term->histpos == term->lstsize
			&& term->save != NULL))
	{
		tputs(tgoto(tgetstr("cr", NULL), 0, term->prevlen), 0, fd_put);
		tputs(tgoto(tgetstr("ce", NULL), 0, term->prevlen), 0, fd_put);
		ft_putstr("\033[33mminishell\033[0m\033[32m~$\033[0m ");
		free(*cmdline);
		*cmdline = NULL;
	}
}

void	help_dhist(t_termcap *term, char **cmdline)
{
	if (term->save != NULL && ft_strlen(term->save) != 0)
	{
		ft_putstr(term->save);
		if (*cmdline != NULL)
			free(*cmdline);
		*cmdline = ft_strdup(term->save);
		term->prevlen = ft_strlen(term->save);
		term->c = ft_strlen(term->save);
	}
	else
		term->prevlen = 0;
}

void	downhistory(t_termcap *term, t_list **history, char **cmdline)
{
	char	**hist_tab;

	delete_dhist(term, cmdline);
	hist_tab = list_to_tabl(*history);
	if (term->histpos < term->lstsize)
		term->histpos +=1;
	if (term->histpos < term->lstsize)
	{
		ft_putstr_fd(hist_tab[term->histpos], 1);
		term->prevlen = ft_strlen(hist_tab[term->histpos]);
	}
	if (term->histpos == term->lstsize)
		help_dhist(term, cmdline);
	if (hist_tab[term->histpos] != NULL)
	{
		free(*cmdline);
		*cmdline = ft_strdup(hist_tab[term->histpos]);
		term->c = ft_strlen(*cmdline);
	}
	free_tabl(hist_tab);
}
