/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:52:09 by esekouni          #+#    #+#             */
/*   Updated: 2023/06/23 15:04:45 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_existe_redirection(char *tokens)
{
	if (ft_strcmp(tokens, ">>") == 0)
		return (1);
	else if (ft_strcmp(tokens, ">") == 0)
		return (1);
	else if (ft_strcmp(tokens, "<") == 0)
		return (1);
	else
		return (0);
}

int	space(char *tokens, char c)
{
	int	i;

	i = 0;
	if (tokens[i] == '\0')
		return (0);
	while (tokens[i])
	{
		if (tokens[i] == '"' && tokens[i + 1] && tokens[i + 1] == '"')
			i += 2;
		else if (tokens[i] == '\'' && tokens[i + 1] && tokens[i + 1] == '\'')
			i += 2;
		else if (tokens[i] != c)
			return (0);
		else if (tokens[i] != '\0')
		i++;
	}
	return (1);
}

char	*remplace_space_and_filtred(char *tmp)
{
	int		i;
	char	x;
	char	*filtred;

	i = 0;
	while (tmp && tmp[i] != '\0')
	{
		if (tmp[i] && (tmp[i] == '\'' || tmp[i] == '"'))
		{
			x = tmp[i];
			i++;
			while (tmp[i] && tmp[i] != x)
				i++;
			if (tmp[i] == '\0')
				break ;
			i++;
		}
		else if (tmp[i] && (tmp[i] == ' ' || tmp[i] == '\t'))
			tmp[i++] = '\x07';
		else if (tmp[i])
			i++;
	}
	filtred = cotes_terminator(tmp);
	return (filtred);
}

int	ambiguous(char	*tokens)
{
	char	*tmp;
	char	**split;
	int		i;

	if (tokens == NULL || tokens[0] == '\0')
		return (2);
	tmp = cotes_terminator(ft_strdup(tokens));
	if (space(tmp, ' ') == 1 || space(tmp, '	') == 1)
	{
		free_pointer(&tmp);
		return (2);
	}
	else
	{
		free_pointer(&tmp);
		tmp = ft_strdup(tokens);
		tmp = remplace_space_and_filtred(tmp);
		split = ft_split(tmp, '\x07');
		i = lent_split(split);
		free_double_pointer(split);
		return (i);
	}
	return (0);
}

int	ambiguous_redirect(char **tokens)
{
	int	i;
	int	j;

	i = 0;
	while (tokens[i])
	{
		if (check_existe_redirection(tokens[i]) == 1)
		{
			i++;
			j = ambiguous(tokens[i]);
			if (j > 1)
			{
				ft_putstr_fd("minishell: ambiguous redirect\n", 2);
				return (1);
			}
			if (tokens[i] != NULL)
				tokens[i] = remplace_space_nonprint(tokens[i]);
			break ;
		}
		i++;
	}
	return (0);
}
