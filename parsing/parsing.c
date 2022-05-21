/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:20:32 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/30 11:11:46 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initail_struct(t_mini *mini)
{
	mini->check_env = "=~\\/%#{}$*+-.:?()@[]^>< \"'";
	mini->smbl = (t_symbol *)malloc(sizeof(t_symbol));
	mini->scmd = NULL;
	mini->under_score = ft_strdup("./minishell");
	mini->smbl->already_pipe = 0;
	mini->file_nme = NULL;
}

void	off_red(t_symbol *smbl)
{
	smbl->read = OFF;
	smbl->write = OFF;
	smbl->append = OFF;
}

void	help_splitpipesemi(t_mini *mini, char *semi, char *pipe)
{
	if (pipe != NULL)
		cf_lstadd_back(&mini->scmd, cf_lst_new(ft_strdup(semi), PIPE));
	else
		cf_lstadd_back(&mini->scmd, cf_lst_new(ft_strdup(semi), END));
}

void	splitpipesemi(t_mini *mini)
{
	int		i;
	int		j;
	char	**pipe;
	char	**semi;

	i = 0;
	mini->glob.exit_pipe = 0;
	mini->glob.fd_in = 0;
	pipe = ft_split(mini->cmdline, '|');
	mini->scmd = NULL;
	while (pipe[i] != NULL)
	{
		j = 0;
		semi = ft_split(pipe[i], ';');
		while (semi[j + 1] != NULL)
		{
			cf_lstadd_back(&mini->scmd, cf_lst_new(ft_strdup(semi[j]), END));
			j++;
		}
		help_splitpipesemi(mini, semi[j], pipe[i + 1]);
		free_tabl(semi);
		i++;
	}
	free_tabl(pipe);
}
