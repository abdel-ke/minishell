/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 16:01:03 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/30 12:18:33 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir(t_mini *mini)
{
	int			ret;
	int			fd;
	t_cflist	*w;
	t_cflist	*r;

	w = NULL;
	r = NULL;
	ret = create_files(mini, &w, &r, &fd);
	if (ret == -1)
		return (ret);
	if (r)
	{
		fd = open(r->name, O_RDONLY);
		dup2(fd, 0);
		close(fd);
	}
	if (w)
	{
		if (w->type == WRITE)
			fd = open(w->name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		else
			fd = open(w->name, O_CREAT | O_WRONLY | O_APPEND, 0666);
		return (fd);
	}
	return (0);
}

int	redir_builtins(t_mini *mini)
{
	int			ret;
	int			fd;
	t_cflist	*w;
	t_cflist	*r;

	w = NULL;
	r = NULL;
	ret = create_files(mini, &w, &r, &fd);
	if (ret == -1)
		return (ret);
	if (r)
	{
		fd = open(r->name, O_RDONLY);
	}
	if (w)
	{
		if (w->type == WRITE)
			fd = open(w->name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		else
			fd = open(w->name, O_CREAT | O_WRONLY | O_APPEND, 0666);
		return (fd);
	}
	return (1);
}
