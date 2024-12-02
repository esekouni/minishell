/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   giga_splite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:17:18 by aouchaad          #+#    #+#             */
/*   Updated: 2023/06/18 19:55:52 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	lenth_cotes_case(t_variables *var, char *input, int i)
{
	if (input[i] == '"' && var->double_cote == 0 && var->single_cote == 0)
		var->double_cote = 1;
	else if (input[i] == '"' && var->double_cote == 1 \
			&& var->single_cote == 0)
	{
		var->double_cote = 0;
		if (input[i + 1] == '\0' || input[i + 1] == ' ' || input[i] == '\t')
		{
			var->lenth++;
			return (1);
		}
	}
	else if (input[i] == '\'' && var->double_cote == 0 && var->single_cote == 0)
		var->single_cote = 1;
	else if (input[i] == '\'' && var->double_cote == 0 \
			&& var->single_cote == 1)
	{
		var->single_cote = 0;
		if (input[i + 1] == '\0' || input[i + 1] == ' ' || input[i] == '\t')
		{
			var->lenth++;
			return (1);
		}
	}
	return (0);
}

int	token_lenth_counter(char *input, int i)
{
	t_variables	var;	

	var.double_cote = 0;
	var.single_cote = 0;
	var.lenth = 0;
	while (input[i])
	{
		if (lenth_cotes_case(&var, input, i) == 1)
			break ;
		else if ((input[i] == ' ' || input[i] == '\t') && var.double_cote == 0 \
				&& var.single_cote == 0)
			break ;
		else if ((input[i] == '|' || input[i] == '<' || input[i] == '>') \
				&& var.double_cote == 0 && var.single_cote == 0)
			break ;
		var.lenth++;
		i++;
	}
	return (var.lenth);
}

static void	variables_init(t_variables *var)
{
	var->token_lenth = 0;
	var->i = 0;
	var->j = 0;
	var->k = 0;
	var->token_start = 0;
	var->lenth = 0;
}

static int	token_lenth(t_variables *var, char *input)
{
	while (input[var->i] && (input[var->i] == ' ' || input[var->i] == '\t'))
		var->i++;
	if (!input[var->i])
		return (1);
	if (input[var->i] == '|' || input[var->i] == '<' || input[var->i] == '>')
	{
		if (input[var->i] && ((input[var->i] == '<' \
				&& input[var->i + 1] == '<') || (input[var->i] == '>' \
				&& input[var->i + 1] == '>')))
			var->token_lenth = 2;
		else
			var->token_lenth = 1;
	}
	else
		var->token_lenth = token_lenth_counter(input, var->i);
	return (0);
}

char	**giga_splite(char *input)
{
	char		**tokens;
	t_variables	var;

	variables_init(&var);
	tokens = malloc(sizeof(char *) * (tokens_counter(input) + 1));
	if (!tokens)
		exit (1);
	while (input[var.i])
	{
		if (token_lenth(&var, input) == 1)
			break ;
		tokens[var.j] = malloc (sizeof(char) * (var.token_lenth + 1));
		if (!tokens[var.j])
		{
			free_double_pointer(tokens);
			exit (1);
		}
		var.k = 0;
		var.token_start = var.i;
		while (var.i < (var.token_start + var.token_lenth))
			tokens[var.j][var.k++] = input[var.i++];
		tokens[var.j++][var.k] = '\0';
	}
	tokens[var.j] = NULL;
	return (tokens);
}
