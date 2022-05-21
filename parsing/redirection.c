/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 18:31:56 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/29 11:41:50 by amouassi         ###   ########.fr       */
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
	if (smbl->read == ON)
		return (62);
	if (smbl->write == ON)
		return (60);
	if (smbl->append == ON)
		return (63);
	return (0);
}

char	*check_redirection(t_symbol *smbl, char *line, int i, int *type)
{
	if (!count_back(line + (i - 1)))
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
					error_red(smbl, 63);
				else
					error_red(smbl, line[i]);
			}
		}
	}
	else
		line[i] *= -1;
	return (line);
}

int	check_flags(t_symbol *smbl)
{
	return (smbl->append + smbl->write + smbl->read + smbl->semi + smbl->pipe);
}
