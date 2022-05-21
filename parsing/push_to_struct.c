/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_to_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 18:32:03 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/28 15:45:16 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_file_name(t_mini *mini, char *line, int *index)
{
	char	*tmp;
	int		pos;
	int		start;
	int		i;

	i = *index;
	pos = i;
	while (line[++i] && line[i] == ' ')
		;
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '>' && line[i] != '<')
		i++;
	if (mini->file_nme)
		free(mini->file_nme);
	mini->file_nme = ft_substr2(line, start, i);
	if (pos && line[pos - 1] == '>')
		--pos;
	line[pos] = 0;
	tmp = ft_strjoin(line, line + i);
	*index = --pos;
	free(line);
	return (tmp);
}

char	*push_read_apnd_strct(t_mini *mini, char *line, int *i)
{
	if (line[(*i) + 1] == '>')
	{
		(*i)++;
		line = get_file_name(mini, line, i);
		file_lstadd_back(&mini->cmds.file,
			file_lst_new(mini->file_nme, APPEND));
	}
	else
	{
		line = get_file_name(mini, line, i);
		file_lstadd_back(&mini->cmds.file,
			file_lst_new(mini->file_nme, WRITE));
	}
	return (line);
}

char	*push_file_struct(t_mini *mini, char *line, int i)
{
	mini->cmds.file = NULL;
	mini->file_nme = NULL;
	while (line[i])
	{
		if (line[i] == '<')
		{
			line = get_file_name(mini, line, &i);
			file_lstadd_back(&mini->cmds.file,
				file_lst_new(mini->file_nme, READ));
		}
		else if (line[i] == '>')
			line = push_read_apnd_strct(mini, line, &i);
		i++;
	}
	if (mini->file_nme)
		free(mini->file_nme);
	return (line);
}

void	push_to_cmd(t_mini *mini)
{
	int	i;

	i = -1;
	while (mini->cmds.cmd[++i])
	{
		if (compare(mini->cmds.cmd[i], "$?")
			|| compare(mini->cmds.cmd[i], "$/"))
			mini->cmds.cmd[i][0] *= -1;
		mini->cmds.cmd[i] = reverse_cmd(mini, mini->cmds.cmd[i], 0, -1);
		if (mini->cmds.cmd[0][0] == '\0')
		{
			free(mini->cmds.cmd[0]);
			mini->cmds.cmd[0] = ft_strdup(" ");
		}
	}
}

void	push_to_struct(t_mini *mini, char *line)
{
	char		*tmp3;
	t_cflist	*tmp;

	tmp3 = ft_strdup(line);
	tmp3 = push_file_struct(mini, tmp3, 0);
	mini->cmds.cmd = ft_split(tmp3, ' ');
	push_to_cmd((mini));
	tmp = mini->cmds.file;
	while (tmp)
	{
		tmp->file_dollar = 1;
		if (tmp->name[0] == '\'' && tmp->name[1] == '$' * -1)
			tmp->file_dollar = 0;
		if (compare(tmp->name, "$?") || compare(tmp->name, "\"$?\""))
			tmp->name = ft_itoa(g_check.exit_status);
		tmp->name = reverse_cmd(mini, tmp->name, 0, -1);
		tmp = tmp->next;
	}
	free(tmp3);
}
