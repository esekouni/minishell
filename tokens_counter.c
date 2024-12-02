/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_counter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:01:29 by aouchaad          #+#    #+#             */
/*   Updated: 2023/05/20 20:22:26 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	single_cote(t_variables *var, char *input)
{
	if (input[var->i] == '\'' && var->double_cote == 0 \
	&& var->single_cote == 0)
		var->single_cote = 1;
	else if (input[var->i] == '\'' && var->double_cote == 0 \
	&& var->single_cote == 1)
	{
		var->single_cote = 0;
		if (input[var->i + 1] && (input[var->i + 1] == ' ' \
		|| input[var->i + 1] == '\t'))
		{
			var->i++;
			return (1);
		}
	}
	return (0);
}

static int	cotes_cases(t_variables *var, char *input)
{
	if (input[var->i] == '"' && var->single_cote == 0 && var->double_cote == 0)
		var->double_cote = 1;
	else if (input[var->i] == '"' && var->single_cote == 0 \
	&& var->double_cote == 1)
	{
		var->double_cote = 0;
		if (input[var->i + 1] && (input[var->i + 1] == ' ' \
		|| input[var->i + 1] == '\t'))
		{
			var->i++;
			return (1);
		}
	}
	else
	{
		if (single_cote(var, input) == 1)
			return (1);
	}
	return (0);
}

static int	redirection_cases(t_variables *var, char *input)
{
	if (input[var->i] == '<' && var->double_cote == 0 && var->single_cote == 0)
	{
		if (input[var->i + 1] && input[var->i + 1] == '<')
			var->i += 2;
		else
			var->i++;
		var->counter++;
		return (1);
	}
	else if (input[var->i] == '>' && var->double_cote == 0 \
	&& var->single_cote == 0)
	{
		if (input[var->i + 1] && input[var->i + 1] == '>')
			var->i += 2;
		else
			var->i++;
		var->counter++;
		return (1);
	}
	return (0);
}

static void	check_cases(t_variables *var, char *input)
{
	while (input[var->i])
	{
		if (input[var->i] == '"' || input[var->i] == '\'')
		{
			if (cotes_cases(var, input) == 1)
				break ;
		}
		else if ((input[var->i] == ' ' || input[var->i] == '\t') \
		&& var->double_cote == 0 && var->single_cote == 0)
			break ;
		else if (input[var->i] == '|' && var->double_cote == 0 \
		&& var->single_cote == 0)
		{
			var->i++;
			var->counter++;
			break ;
		}
		else if (redirection_cases(var, input) == 1)
			break ;
		var->i++;
	}
}

int	tokens_counter(char *input)
{
	t_variables	var;

	var.i = 0;
	var.counter = 0;
	var.single_cote = 0;
	var.double_cote = 0;
	while (input[var.i])
	{
		while (input[var.i] && (input[var.i] == ' ' || input[var.i] == '\t'))
			var.i++;
		if (input[var.i] && input[var.i] != ' ' && input[var.i] != '\t' \
		&& input[var.i] != '|' && input[var.i] != '<' && input[var.i] != '>')
			var.counter++;
		check_cases(&var, input);
	}
	return (var.counter);
}
