/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remplace_space_nonprint.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:35:40 by esekouni          #+#    #+#             */
/*   Updated: 2023/06/23 15:14:58 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_remplace_space_nonprint(char	*tokens,
		t_variables *var, char *filtred)
{
	char	x;

	if (tokens[var->i] && (tokens[var->i] == '\''
			|| tokens[var->i] == '"'))
	{
		filtred[var->j++] = tokens[var->i];
		x = tokens[var->i++];
		while (tokens[var->i] && tokens[var->i] != x)
			filtred[var->j++] = tokens[var->i++];
		if (tokens[var->i] == '\0')
			return (1);
	filtred[var->j++] = tokens[var->i];
		var->i++;
	}
	else if (tokens[var->i] && (tokens[var->i] == ' '
			|| tokens[var->i] == '\t'))
	{
		filtred[var->j++] = '\x05';
		var->i++;
	}
	else if (tokens[var->i])
		filtred[var->j++] = tokens[var->i++];
	return (0);
}

char	*remplace_space_nonprint(char *tokens)
{
	t_variables	var;
	char		*filtred;

	var.len = ft_strlen(tokens);
	filtred = malloc(sizeof(char) * var.len + 1);
	if (!filtred)
		exit (1);
	var.i = 0;
	var.j = 0;
	while (tokens[var.i] && tokens[var.i] != '\0')
	{
		if (fill_remplace_space_nonprint(tokens, &var, filtred) == 1)
			break ;
	}
	filtred[var.j] = '\0';
	free_pointer(&tokens);
	return (filtred);
}
