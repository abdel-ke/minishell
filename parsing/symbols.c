/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 17:02:55 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/30 12:18:03 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initial_symbol(t_symbol *sbl)
{
	sbl->pipe = OFF;
	sbl->semi = OFF;
	sbl->s_quote = OFF;
	sbl->d_quote = OFF;
	sbl->read = OFF;
	sbl->write = OFF;
	sbl->append = OFF;
	sbl->error = OFF;
}

char	*check_d_quote(t_symbol *smbl, char *line, int i)
{
	if (!count_back(line + (i - 1)))
	{
		if (smbl->pipe == ON)
			smbl->pipe = OFF;
		if (smbl->d_quote == OFF && smbl->s_quote == OFF)
			smbl->d_quote = ON;
		else if (smbl->d_quote == ON && smbl->s_quote == OFF)
			smbl->d_quote = OFF;
		else if (smbl->s_quote == ON)
			line[i] *= -1;
		off_red(smbl);
	}
	else if (smbl->d_quote == ON)
		line[i] *= -1;
	return (line);
}

char	*check_s_quote(t_symbol *smbl, char *line, int i)
{
	if (smbl->s_quote == OFF && smbl->d_quote == OFF)
	{
		if (smbl->pipe == ON)
			smbl->pipe = OFF;
		if (!count_back(line + (i - 1)))
			smbl->s_quote = ON;
		off_red(smbl);
	}
	else
	{
		if (smbl->s_quote == ON)
			smbl->s_quote = OFF;
		else if (smbl->d_quote == ON)
			line[i] *= -1;
	}
	return (line);
}

char	*check_space(t_symbol *smbl, char *line, int i)
{
	if (smbl->d_quote == ON || smbl->s_quote == ON)
		line[i] *= -1;
	else if (smbl->d_quote == OFF && smbl->s_quote == OFF
		&& count_back(line + i - 1))
		line[i] *= -1;
	return (line);
}

char	*check_symbols(t_symbol *smbl, char *line, int i)
{
	while (line[++i] && !smbl->error)
	{
		if (line[i] == '"')
			line = check_d_quote(smbl, line, i);
		else if (line[i] == '\'')
			line = check_s_quote(smbl, line, i);
		else if (line[i] == '|')
			line = check_pipe(smbl, line, i);
		else if (line[i] == ';')
			line = check_semicolone(smbl, line, i);
		else if (line[i] == '>' && line[i + 1] == '>')
			line = check_redirection(smbl, line, i++, &smbl->append);
		else if (line[i] == '>')
			line = check_redirection(smbl, line, i, &smbl->read);
		else if (line[i] == '<')
			line = check_redirection(smbl, line, i, &smbl->write);
		else if (line[i] == ' ')
			line = check_space(smbl, line, i);
		else if (check_flags(smbl) && line[i] != ' ')
			off_flags(smbl);
		if ((line[i] == '$' && smbl->s_quote == ON)
			|| (line[i] == '$' && line[i + 1] == ' ' && smbl->d_quote == ON))
			line[i] *= -1;
	}
	return (line);
}
