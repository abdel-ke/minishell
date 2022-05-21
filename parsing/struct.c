/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:22:04 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/29 14:48:56 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_new_env_element(t_env *curr_node, char *env)
{
	int		len;

	len = 0;
	while (env[len] != '\0' && env[len] != '=')
		len++;
	curr_node->name = ft_substr(env, 0, len);
	curr_node->value = ft_strdup(env + len + 1);
	curr_node->next = NULL;
}

t_cflist	*file_lst_new(void *filename, int filetype)
{
	t_cflist	*head;

	head = (t_cflist *)malloc(sizeof(t_cflist));
	if (head == NULL)
		return (NULL);
	head->name = ft_strdup(filename);
	head->type = filetype;
	head->next = NULL;
	return (head);
}

void	file_lstadd_back(t_cflist **alst, t_cflist *new)
{
	t_cflist	*temp;

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

t_env	*create_env_list(char **env)
{
	t_env	*env_list;
	t_env	*curr_node;
	int		i;

	env_list = malloc(sizeof(t_env));
	curr_node = env_list;
	add_new_env_element(curr_node, env[0]);
	i = 1;
	while (env[i])
	{
		curr_node->next = malloc(sizeof(t_env));
		curr_node = curr_node->next;
		add_new_env_element(curr_node, env[i]);
		i++;
	}
	return (env_list);
}
