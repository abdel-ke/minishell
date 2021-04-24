/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 17:02:55 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/22 16:53:27 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initial_symbol(t_symbol *sbl)
{
	sbl->pipe = OFF;
	sbl->semi = OFF;
	sbl->s_quote = OFF;
	sbl->d_quote = OFF;
	sbl->great = OFF;
	sbl->less = OFF;
	sbl->d_great = OFF;
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
	}
	else if (smbl->d_quote == ON)
		line[i] *= -1;
	return (line);
}

char	*check_s_quote(t_symbol *smbl, char *line, int i)
{
	if (smbl->s_quote == OFF && smbl->d_quote == OFF)
	{
		if (smbl->d_great == ON)
			smbl->d_great = OFF;
		if (smbl->great == ON)
			smbl->great = OFF;
		if (smbl->less == ON)
			smbl->less = OFF;
		if (!count_back(line + (i - 1)))
			smbl->s_quote = ON;
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
			line = check_redirection(smbl, line, i++, &smbl->d_great);
		else if (line[i] == '>')
			line = check_redirection(smbl, line, i, &smbl->great);
		else if (line[i] == '<')
			line = check_redirection(smbl, line, i, &smbl->less);
		else if (line[i] == ' ')
			line = check_space(smbl, line, i);
		else if (line[i] == '$')
			line = ft_turn_dollar(smbl, line, i);
		else if (check_flags(smbl) && line[i] != ' ')
			off_flags(smbl);
	}
	return (line);
}
