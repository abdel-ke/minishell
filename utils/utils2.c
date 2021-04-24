/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 21:29:23 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/22 11:56:43 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	help_search_replace(char *str, char *org, char *rep, char *new)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (ft_strnstr(str, org, ft_strlen(str)) == str)
		{
			ft_strcpy(&new[i], rep);
			i += ft_strlen(rep);
			str += ft_strlen(org);
		}
		else
			new[i++] = *str++;
	}
	new[i++] = '\0';
}

char	*search_replace(char *str, char *org, char *rep)
{
	int		i;
	int		count;
	char	*new;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_strstr(&str[i], org) == &str[i])
		{
			count++;
			i += ft_strlen(org) - 1;
		}
		i++;
	}
	new = (char *)malloc(i + count * (ft_strlen(rep) - ft_strlen(org)) + 1);
	help_search_replace(str, org, rep, new);
	return (new);
}

int	ft_sort_str(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] > s2[i])
		{
			return (1);
		}
		else if (s1[i] < s2[i])
			return (2);
		i++;
	}
	return (0);
}

void	ft_sort_tabl(char **tabll)
{
	char	*s;
	int		d;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tabll[i] != NULL)
	{
		j = 0;
		while (tabll[j] != NULL)
		{
			d = ft_sort_str(tabll[i], tabll[j]);
			if (d == 2)
			{
				s = tabll[i];
				tabll[i] = tabll[j];
				tabll[j] = s;
			}
			j++;
		}
		i++;
	}
}

int	check_isnumeriq(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
