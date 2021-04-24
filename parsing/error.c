/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 18:30:33 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/20 15:40:06 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	off_flags(t_symbol *smbl)
{
	smbl->d_great = 0;
	smbl->less = 0;
	smbl->great = 0;
	smbl->semi = 0;
	smbl->pipe = 0;
}

void	ft_error(t_symbol *smbl, char *str)
{
	ft_putstr_fd(RED, 1);
	ft_putendl_fd(str, 1);
	ft_putstr_fd(WHITE, 1);
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

void	error_red(t_symbol *smbl, char *error, char c)
{
	if (c == 63)
		printf("%s%s `%s'%s\n", RED, error, ">>", WHITE);
	else
		printf("%s%s `%c'%s\n", RED, error, c, WHITE);
	smbl->error = 1;
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
			ft_error(smbl, "bash: syntax error near unexpected token `||'");
		else
			ft_error(smbl, "bash: syntax error near unexpected token `|'");
	}
	if (line[0] == ';')
	{
		if (line[1] == ';')
			ft_error(smbl, "bash: syntax error near unexpected token `;;'");
		else
			ft_error(smbl, "bash: syntax error near unexpected token `;'");
	}
	line = check_symbols(smbl, line, -1);
	if (!smbl->error && (smbl->d_great || smbl->d_quote || smbl->s_quote
			|| smbl->pipe || smbl->great || smbl->less))
		ft_error(smbl, "syntax error near unexpected token `newline'");
	return (line);
}
