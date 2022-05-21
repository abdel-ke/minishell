/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:33:24 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/30 11:23:14 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path_dollar(t_mini *mini, char *line, int *j)
{
	while (line[++(*j)])
		if (ft_strchr(mini->check_env, line[*j])
			|| line[*j] == ' ' * -1 || line[*j] == '\'' * -1
			|| line[*j] == '|' * -1 || line[*j] == ';' * -1
			|| line[*j] == '<' * -1 || line[*j] == '>' * -1
			|| line[*j] == '$' * -1)
			break ;
	line = ft_substr(line, 0, *j);
	return (line);
}

char	*add_dollar_path(char *path)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * ft_strlen(path) + 2);
	new[0] = '$' * -1;
	while (path[i])
	{
		new[i + 1] = path[i];
		i++;
	}
	return (new);
}

char	*file_dollar(char *line, char *path)
{
	char	*path2;
	char	*new_line;

	path2 = add_dollar_path(path);
	new_line = ft_strjoin(path2, line);
	free(path2);
	return (new_line);
}
