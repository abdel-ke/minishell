/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 18:31:56 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/22 16:50:13 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr2(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (start < len)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

int	compare(char *str, char *str2)
{
	while (*str || *str2)
	{
		if (*str != *str2)
			return (0);
		str++;
		str2++;
	}
	return (1);
}

int	redirection(t_symbol *smbl)
{
	if (smbl->great == ON)
		return (62);
	if (smbl->less == ON)
		return (60);
	if (smbl->d_great == ON)
		return (63);
	return (0);
}

char	*check_redirection(t_symbol *smbl, char *line, int i, int *type)
{
	if (smbl->d_quote == ON || smbl->s_quote == ON)
	{
		if (line[i + 1] == '>')
			line[i + 1] *= -1;
		line[i] *= -1;
	}
	else
	{
		if (redirection(smbl) == OFF)
			*type = ON;
		else
		{
			if (line[i + 1] == '>')
				error_red(smbl, "syntax error near unexpected token", 63);
			else
				error_red(smbl, "syntax error near unexpected token", line[i]);
		}
	}
	return (line);
}

int	check_flags(t_symbol *smbl)
{
	int	sum;

	sum = smbl->d_great + smbl->less + smbl->great + smbl->semi + smbl->pipe;
	return (sum);
}
