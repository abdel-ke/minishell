/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:37:46 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/29 13:34:01 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	help_dollar_digit(char **line, char *new, int *i)
{
	char	*tmp;
	char	*line2;

	line2 = *line;
	line2[*i] = 0;
	tmp = ft_strjoin(line2, new);
	if (line2)
		free(line2);
	line2 = tmp;
	if (line2[*i] == '$')
		*i = -1;
	else
		*i = 0;
	if (new != NULL)
		free(new);
	*line = line2;
}

char	*dollar_digit(char *line, int *i)
{
	char	*new;

	if (line[*i + 1] == '0')
	{
		new = ft_strjoin("minishell", line + (*i) + 2);
		help_dollar_digit(&line, new, i);
	}
	else
	{
		new = ft_strdup(line + (*i) + 2);
		help_dollar_digit(&line, new, i);
	}
	return (line);
}

char	*help_dollar_simple(char *line, char *new)
{
	char	*tmp2;
	char	*itoa;
	char	*tmp;

	itoa = ft_itoa(g_check.exit_status);
	tmp2 = ft_strjoin(itoa, new + 1);
	tmp = ft_strjoin(line, tmp2);
	free(itoa);
	free(tmp2);
	return (tmp);
}

char	*dollar_simple(t_mini *mini, char *line, int *i)
{
	char	*new;
	char	*tmp;

	new = dollar(mini, line + *i + 1);
	line[*i] = 0;
	if (new[0] == '?')
		tmp = help_dollar_simple(line, new);
	else
		tmp = ft_strjoin(line, new);
	if (line[*i] == '$')
		*i = -1;
	else
		*i = 0;
	if (line)
		free(line);
	line = tmp;
	if (new != NULL)
		free(new);
	return (line);
}
