/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files_err.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:02:24 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/26 16:07:49 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_file_perm(t_cflist *file)
{
	struct stat		buf;
	int				status;

	status = stat(file->name, &buf);
	if (status == 0)
	{
		if ((buf.st_mode & S_IRUSR) == 0)
			return (3);
		if ((buf.st_mode & S_IWUSR) == 0)
			return (1);
		return (2);
	}
	return (0);
}

int	wapp_error(t_cflist *tmp, int *fd)
{
	int	perm;

	perm = check_file_perm(tmp);
	if (perm == 1)
	{
		error_permission(tmp->name);
		g_check.exit_status = -2;
		close(*fd);
		return (-1);
	}
	if (perm == 2 && *fd == -1)
	{
		error_dir(tmp->name);
		g_check.exit_status = -2;
		close(*fd);
		return (-1);
	}
	if (*fd == -1)
	{
		error_file_nodir(tmp->name);
		g_check.exit_status = -2;
		close(*fd);
		return (-1);
	}
	return (0);
}

int	r_error(t_cflist *tmp, int *fd)
{
	int	perm;

	perm = check_file_perm(tmp);
	if (perm == 3)
	{
		error_permission(tmp->name);
		g_check.exit_status = -2;
		close(*fd);
		return (-1);
	}
	if (perm == 2 && *fd == -1)
	{
		error_dir(tmp->name);
		g_check.exit_status = -2;
		close(*fd);
		return (-1);
	}
	if (*fd == -1)
	{
		error_file_nodir(tmp->name);
		g_check.exit_status = -2;
		close(*fd);
		return (-1);
	}
	return (0);
}
