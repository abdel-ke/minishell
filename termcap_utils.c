/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:50:01 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/29 11:51:51 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	help_delete(t_termcap *term)
{
	tputs(tgoto(tgetstr("LE", NULL), 0, 1), 0, fd_put);
	tputs(tgoto(tgetstr("ce", NULL), 0, 1), 0, fd_put);
	if (((term->c + 12) % term->win.ws_col) == 0)
	{
		tputs(tgoto(tgetstr("up", NULL), 0, 1), 0, fd_put);
		tputs(tgoto(tgetstr("RI", NULL), 0, term->win.ws_col), 0, fd_put);
		tputs(tgoto(tgetstr("ce", NULL), 0, 1), 0, fd_put);
	}
}

void	delete(char **cmdline, t_termcap *term)
{
	char	*tmp;
	char	*tmp2;

	if (term->c > 0)
		help_delete(term);
	if (term->c > 0)
		term->c -= 1;
	if (term->save != NULL && ft_strcmp(term->save, *cmdline) == 0)
	{
		tmp2 = ft_strdup(term->save);
		free(term->save);
		term->save = ft_substr(tmp2, 0, ft_strlen(tmp2) - 1);
		free(tmp2);
	}
	tmp = ft_strdup(*cmdline);
	free(*cmdline);
	*cmdline = ft_substr(tmp, 0, term->c);
	free(tmp);
	tmp = NULL;
	if (term->prevlen > 0)
		term->prevlen -= 1;
}
