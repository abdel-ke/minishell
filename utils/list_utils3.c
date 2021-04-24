/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 11:25:03 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/22 11:34:12 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cflist	*cf_lst_new(void *name, int type)
{
	t_cflist	*head;

	head = (t_cflist *)malloc(sizeof(t_cflist));
	if (head == NULL)
		return (NULL);
	head->name = name;
	head->type = type;
	head->next = NULL;
	return (head);
}

void	cf_lstadd_back(t_cflist **alst, t_cflist *new)
{
	t_cflist		*temp;

	if (!alst || !new)
		return ;
	temp = *alst;
	if (temp != NULL)
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new;
		new->next = NULL;
	}
	else
	{
		*alst = new;
		new->next = NULL;
	}
}

void	cf_lstdelone(t_cflist *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->name);
	free(lst);
}

void	cf_lstclear(t_cflist **lst, void (*del)(void*))
{
	t_cflist	*temp;

	if (!lst || !*lst || !del)
		return ;
	while (*lst != NULL)
	{
		temp = *lst;
		*lst = (*lst)->next;
		cf_lstdelone(temp, del);
	}
	*lst = NULL;
}
