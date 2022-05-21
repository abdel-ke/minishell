/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:41:48 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/29 16:30:24 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_env(char *str, t_list **env)
{
	t_list	*runner;
	t_list	*previous;
	char	**split;

	previous = NULL;
	runner = *env;
	while (runner)
	{
		split = ft_split(runner->content, '=');
		if (ft_strcmp(str, split[0]) == 0)
		{
			if (previous)
				previous->next = runner->next;
			if (!previous)
				*env = runner->next;
			ft_lstdelone(runner, free);
			free_tabl(split);
			break ;
		}
		free_tabl(split);
		previous = runner;
		runner = runner->next;
	}
}
