/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:17:56 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/22 11:58:37 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_spec_char_export(char *str)
{
	char	*spec_char;
	int		i;
	int		j;

	spec_char = "!#$&()*+-./:;<>?@[^]_{}~%";
	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (spec_char[j] != '\0')
		{
			if (str[i] == spec_char[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_spec_char_unset(char *str)
{
	char	*spec_char;
	int		i;
	int		j;

	spec_char = "!#$&()*+-./:;<=>?@[^]{}~%=";
	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (spec_char[j] != '\0')
		{
			if (str[i] == spec_char[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	help_check_syntax_export(char **split)
{
	if (ft_strcmp(split[0], "=") == 0)
	{
		free_tabl(split);
		return (1);
	}
	else if (split[0][0] == '=')
	{
		free_tabl(split);
		return (1);
	}
	else if (ft_isdigit(split[0][0]) == 1)
	{
		free_tabl(split);
		return (1);
	}
	return (0);
}

int	check_syntax_export(char *cmd)
{
	char	**split;

	if (ft_strncmp(cmd, "=", 1) == 0)
		return (1);
	split = ft_split(cmd, '=');
	if (ft_strcmp(split[0], "=") == 0 || split[0][0] == '='
		|| ft_isdigit(split[0][0]) == 1)
	{
		if (help_check_syntax_export(split) == 1)
			return (1);
	}
	else if (check_spec_char_export(split[0]) == 1)
	{
		free_tabl(split);
		return (1);
	}
	free_tabl(split);
	return (0);
}

int	check_syntax_unset(char *cmd)
{
	if (ft_strcmp(cmd, "=") == 0)
		return (1);
	else if (ft_isdigit(cmd[0]) == 1)
		return (1);
	else if (check_spec_char_unset(cmd) == 1)
		return (1);
	return (0);
}
