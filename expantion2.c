/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esekouni <esekouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:20:51 by esekouni          #+#    #+#             */
/*   Updated: 2023/06/22 13:40:12 by esekouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cat_string_start_end(char *tokens, int start, int end)
{
	char	*ch;
	int		i;

	ch = malloc(sizeof(char) * (end - start + 1));
	if (!ch)
		return (NULL);
	i = 0;
	while (start < end)
		ch[i++] = tokens[start++];
	ch[i] = '\0';
	free_pointer(&tokens);
	return (ch);
}

char	*name_variable(char *split, t_variables *variable_index)
{
	t_variables	var;
	char		*variable;

	var.i = 0;
	var.len = 0;
	while (split[var.i] && (split[var.i] != '$'))
		var.i++;
	var.i++;
	while (split[var.i] && check_valid_caractr(split[var.i]) == 0)
	{
		variable_index->i++;
		var.len++;
		var.i++;
	}
	variable = malloc(sizeof(char) * (var.len + 1));
	if (!variable)
		return (NULL);
	var.i = var.i - var.len;
	var.len = 0;
	while (split[var.i] && check_valid_caractr(split[var.i]) == 0)
		variable[var.len++] = split[var.i++];
	variable[var.len] = '\0';
	return (variable);
}

char	*check_cotes_after_dollar(char *split, t_variables *var, char before)
{
	if ((split[var->i + 1] == '"' && before == '"'))
		return (ft_strdup("$"));
	else if ((split[var->i + 1] == '\'' && before == '\''))
		return (ft_strdup("$"));
	else if ((before == '\0' && split[var->i + 1] != '\''
			&& split[var->i + 1] != '"'))
		return (ft_strdup("$"));
	else if (before != '\0' && (split[var->i + 1] == '\''
			|| split[var->i + 1] == '"'))
		return (ft_strdup("$"));
	else
		return (ft_strdup(""));
}

char	*check_after_dollar2(char *split, t_variables *variable,
		t_variables *var)
{
	if (split[var->i] && split[var->i] == '$'
		&& ft_isalnum(split[var->i + 1]) == 0)
	{
		var->j = var->i;
		variable->i++;
		while (split[++(var->i)] && split[var->i] != '$'
			&& split[var->i] != '"' && split[var->i] != '\'')
			variable->i++;
		return (cat_string_start_end(ft_strdup(split), var->j, var->i));
	}
	if (var->i < ft_strlen(split) && ft_isdigit(split[var->i + 1]) == 1)
	{
		var->i += 2;
		var->j = var->i;
		variable->i++;
		while (split[var->i] && split[var->i] != '$'
			&& split[var->i] != '"' && split[var->i] != '\'')
		{
			var->i++;
			variable->i++;
		}
		return (cat_string_start_end(ft_strdup(split), var->j, var->i));
	}
	return (NULL);
}

char	*check_after_dollar(char *split, char before,
		t_variables *variable, t_glob *glob)
{
	t_variables	var;

	var.i = 0;
	while (split[var.i] && (split[var.i] != '$'))
		var.i++;
	if (split[var.i] && split[var.i] == '$' && (split[var.i + 1] == '"'
			|| split[var.i + 1] == '\''))
	{
		variable->i++;
		return (check_cotes_after_dollar(split, &var, before));
	}
	if (split[var.i] && split[var.i] == '$' && split[var.i + 1] == '?')
	{
		variable->i++;
		return (ft_itoa((glob)->exit_stat));
	}
	if (split[var.i] && split[var.i] == '$' && split[var.i + 1] == '_')
		return (NULL);
	return (check_after_dollar2(split, variable, &var));
}
