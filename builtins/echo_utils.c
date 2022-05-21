/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 15:32:23 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/26 15:34:51 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_n(char *str)
{
	int	i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	get_n(char **cmd, int *b)
{
	int		i;

	i = 1;
	while (cmd[i] != NULL && (ft_strncmp(cmd[1], "-", 1) == 0
			&& check_n(cmd[i]) == 0))
	{
		*b = 1;
		i++;
	}
	return (i);
}
