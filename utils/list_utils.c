/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 11:11:33 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/29 16:27:50 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	help_sort_list(t_list *tmp)
{
	t_list	*index;
	char	*temp;

	while (tmp != NULL)
	{
		index = tmp->next;
		while (index != NULL)
		{
			if (ft_sort_str(tmp->content, index->content) == 1)
			{
				temp = tmp->content;
				tmp->content = index->content;
				index->content = temp;
			}
			index = index->next;
		}
		tmp = tmp->next;
	}
}

void	sort_list(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	if (list == NULL)
		return ;
	else
		help_sort_list(tmp);
}

void	print_list(t_list *list, int fd)
{
	t_list	*tmp;

	tmp = list;
	if (list == NULL)
		return ;
	else
	{
		while (tmp != NULL)
		{
			if (ft_strncmp(tmp->content, "_=", 2) != 0)
				ft_putendl_fd(tmp->content, fd);
			tmp = tmp->next;
		}
	}
}

char	**list_to_tabl(t_list *list)
{
	t_list	*tmp;
	char	**tabl;
	int		i;

	tmp = list;
	i = 0;
	tabl = malloc((ft_lstsize(tmp) + 1) * sizeof(char *));
	while (tmp != NULL)
	{
		tabl[i] = ft_strndup(tmp->content, ft_strlen(tmp->content));
		tmp = tmp->next;
		i++;
	}
	tabl[i] = NULL;
	return (tabl);
}

t_list	*init_list(void)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	return (list);
}
