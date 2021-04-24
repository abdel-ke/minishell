/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:41:48 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/22 14:19:45 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_pos(t_list *list, char *name)
{
	t_list	*tmp;
	int		pos;
	char	**split;

	tmp = list;
	pos = 0;
	while (tmp != NULL)
	{
		split = ft_split(tmp->content, '=');
		if (ft_strncmp(split[0], name, ft_maxlen(split[0], name)) == 0)
		{
			free_tabl(split);
			return (pos);
		}
		pos++;
		tmp = tmp->next;
		free_tabl(split);
	}
	return (-1);
}

int	help_delete_node(int position, t_list *list)
{
	t_list	*temp;
	t_list	*next;
	int		i;

	temp = list;
	i = 0;
	if (position == 0)
	{
		list = temp->next;
		ft_lstdelone(temp, free);
		return (1);
	}
	while (temp != NULL && i < position - 1)
	{
		 temp = temp->next;
		 i++;
	}
	if (temp == NULL || temp->next == NULL)
		 return (1);
	next = temp->next->next;
	ft_lstdelone(temp->next, free);
	temp->next = next;
	return (0);
}

void	delete_node(t_list *list, char *name)
{
	int		position;

	position = find_pos(list, name);
	if (position == -1)
		return ;
	if (list == NULL)
		return ;
	if (help_delete_node(position, list) == 1)
		return ;
}
