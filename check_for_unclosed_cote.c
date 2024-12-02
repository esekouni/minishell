/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_unclosed_cote.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 22:08:06 by aouchaad          #+#    #+#             */
/*   Updated: 2023/06/22 11:37:55 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cotes_cases(t_variables *var, char *input)
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
}

int	check_for_unclosed_cote(char *input)
{
	t_variables	var;

	var.i = 0;
	var.double_cote = 0;
	var.single_cote = 0;
	while (input[var.i])
	{
		if (input[var.i] == '"' || input[var.i] == '\'')
			cotes_cases(&var, input);
		var.i++;
	}
	if (var.single_cote == 1 || var.double_cote == 1)
	{
		if (var.single_cote == 1)
			printf("minishell: syntax error\n");
		else
			printf("minishell: syntax error\n");
		return (1);
	}
	return (0);
}
