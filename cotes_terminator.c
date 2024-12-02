/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cotes_terminator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:34:29 by aouchaad          #+#    #+#             */
/*   Updated: 2023/06/18 18:49:02 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	variables_init(t_variables *var)
{
	var->i = 0;
	var->j = 0;
	var->double_cote = 0;
	var->single_cote = 0;
}

static void	cotes_cases(t_variables *var, char *input, char *command)
{
	if (input[var->i] == '"' && var->single_cote == 0 \
			&& var->double_cote == 0)
		var->double_cote = 1;
	else if (input[var->i] == '"' && var->single_cote == 0 \
			&& var->double_cote == 1)
		var->double_cote = 0;
	else if (input[var->i] == '\'' && var->double_cote == 0 \
			&& var->single_cote == 0)
		var->single_cote = 1;
	else if (input[var->i] == '\'' && var->double_cote == 0 \
			&& var->single_cote == 1)
		var->single_cote = 0;
	else
		command[var->j++] = input[var->i];
}

char	*cotes_terminator(char *input)
{
	char		*command;
	t_variables	var;

	command = malloc (sizeof(char) * (ft_strlen(input) + 1));
	if (!command)
	{
		free_pointer(&input);
		return (NULL);
	}
	variables_init(&var);
	while (input[var.i])
	{
		if (input[var.i] != '"' && input[var.i] != '\'')
			command[var.j++] = input[var.i];
		else if (input[var.i] == '"' || input[var.i] == '\'')
			cotes_cases(&var, input, command);
		var.i++;
	}
	command[var.j] = '\0';
	free_pointer(&input);
	return (command);
}
