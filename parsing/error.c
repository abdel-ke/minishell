/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 18:30:33 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/27 14:37:50 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	off_flags(t_symbol *smbl)
{
	smbl->append = 0;
	smbl->write = 0;
	smbl->read = 0;
	smbl->semi = 0;
	smbl->pipe = 0;
}

void	ft_error(t_symbol *smbl, char *str)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putendl_fd(str, 1);
	g_check.exit_status = 258;
	smbl->error = ON;
}

int	count_back(char *line)
{
	int	cp;

	cp = 0;
	while (*line == '\\')
	{
		cp++;
		line--;
	}
	if (cp % 2 == 0)
		return (0);
	return (1);
}

void	error_red(t_symbol *smbl, char c)
{
	if (c == 63)
		ft_error(smbl, "syntax error near unexpected token `>>'");
	else
	{
		if (c == '>')
			ft_error(smbl, "syntax error near unexpected token `>'");
		else if (c == '<')
			ft_error(smbl, "syntax error near unexpected token `<'");
	}
}

char	*partition_stage(t_symbol *smbl, char *line)
{
	int	i;

	i = 0;
	initial_symbol(smbl);
	line = ft_strtrim(line, " ");
	if (line[0] == '|')
	{
		if (line[1] == '|')
			ft_error(smbl, "syntax error near unexpected token `||'");
		else
			ft_error(smbl, "syntax error near unexpected token `|'");
	}
	if (line[0] == ';')
	{
		if (line[1] == ';')
			ft_error(smbl, "syntax error near unexpected token `;;'");
		else
			ft_error(smbl, "syntax error near unexpected token `;'");
	}
	line = check_symbols(smbl, line, -1);
	if (!smbl->error && (smbl->append || smbl->d_quote || smbl->s_quote
			|| smbl->pipe || smbl->read || smbl->write))
		ft_error(smbl, "syntax error near unexpected token `newline'");
	return (line);
}
