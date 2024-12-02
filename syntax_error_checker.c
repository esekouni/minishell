/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:14:38 by aouchaad          #+#    #+#             */
/*   Updated: 2023/06/23 15:00:24 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cotes_cases(t_variables *var, char car)
{
	if (car == '\'' && var->single_cote == 0 \
	&& var->double_cote == 0)
		var->single_cote = 1;
	else if (car == '\'' && var->single_cote == 1 \
	&& var->double_cote == 0)
		var->single_cote = 0;
	else if (car == '\"' && var->double_cote == 0 \
	&& var->single_cote == 0)
		var->double_cote = 1;
	else if (car == '\"' && var->double_cote == 1 \
	&& var->single_cote == 0)
		var->double_cote = 0;
}

int	check_for_cotes(char *av, int i)
{
	t_variables	var;

	var.double_cote = 0;
	var.single_cote = 0;
	while (av[i])
	{
		if (av[i] == '\'' || av[i] == '"')
			cotes_cases(&var, av[i]);
		i++;
	}
	if (var.single_cote == 1 || var.double_cote == 1)
	{
		if (var.double_cote == 1)
			printf("minishell: unexpected EOF while looking for matching\n");
		else
			printf("minishell: unexpected EOF while looking for matching\n");
		return (1);
	}
	return (0);
}

static int	check_caracter(t_variables *var, char *av)
{
	int	j;

	if (av[var->i] == '\'' || av[var->i] == '"')
		cotes_cases(var, av[var->i]);
	else if ((av[var->i] == '<' || av[var->i] == '>' || av[var->i] == '|') \
	&& var->single_cote == 0 && var->double_cote == 0)
	{
		j = syntax_error(av, var->i);
		if (j == 1)
			return (1);
		if (j == 0)
			var->count++;
		if (var->count == 3)
		{
			printf("minishell: syntax error\n");
			return (1);
		}
	}
	else if (av[var->i] != ' ' && av[var->i] != '\t')
		var->count = 0;
	return (0);
}

int	check_syntax(char *av)
{
	t_variables	var;

	var.i = 0;
	var.double_cote = 0;
	var.single_cote = 0;
	var.count = 0;
	while (av[var.i] && (av[var.i] == ' ' || av[var.i] == '\t'))
		var.i++;
	if (av[var.i] == '|')
	{
		printf("minishell: syntax error\n");
		return (1);
	}
	if (check_for_cotes(av, var.i) == 1)
		return (1);
	while (av[var.i])
	{
		if (check_caracter(&var, av) == 1)
			return (1);
		var.i++;
	}
	return (0);
}
