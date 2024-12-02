/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esekouni <esekouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:20:19 by esekouni          #+#    #+#             */
/*   Updated: 2023/06/22 14:26:58 by esekouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*print_valeur_dollar(char *split, char before,
		t_glob *glob, t_variables *var)
{
	char				*variable;
	char				*valeur;

	variable = check_after_dollar(split, before, var, glob);
	if (variable != NULL)
		return (variable);
	variable = name_variable(split, var);
	variable = ft_sssstrjoin(ft_strdup("declare -x "), variable);
	valeur = found_valeur_variable(glob->export, variable);
	if (ft_strlen(valeur) == 0)
	{
		free_pointer(&valeur);
		free_pointer(&variable);
		return (ft_strdup(""));
	}
	else
	{
		valeur = cat_string_start_end(valeur, 1, (ft_strlen(valeur) - 1));
		valeur = add_nprin(valeur);
	}
	free_pointer(&variable);
	return (valeur);
}

int	ft_strlen_filter_dollar(char *tokens)
{
	t_variables	var;

	var.i = 0;
	var.len = 0;
	while (tokens[var.i] != '\0')
	{
		if (tokens[var.i] == '$')
		{
			while (tokens[var.i] && tokens[var.i] == '$')
				var.i++;
			var.len++;
		}
		else
		{
			var.len++;
			var.i++;
		}
	}
	return (var.len);
}

char	*fill_filtred_string(char *tokens, char *filtred_dollar)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (tokens[i] == '$')
		{
			count = 0;
			i--;
			while (tokens[++i] && tokens[i] == '$')
				count++;
			if (count % 2 != 0)
				filtred_dollar[j++] = '$';
			else
				filtred_dollar[j++] = '\x07';
		}
		else
			filtred_dollar[j++] = tokens[i++];
	}
	filtred_dollar[j] = '\0';
	return (filtred_dollar);
}

char	*filter_dollar(char *tokens)
{
	char		*filtred_dollar;
	t_variables	var;

	var.len = ft_strlen_filter_dollar(tokens);
	filtred_dollar = malloc (sizeof(char) * var.len + 1);
	if (!filtred_dollar)
	{
		free_pointer(&tokens);
		return (NULL);
	}
	filtred_dollar = fill_filtred_string(tokens, filtred_dollar);
	free_pointer(&tokens);
	return (filtred_dollar);
}

void	expantion_single_cote(char **join, char *tokens, t_variables	*var)
{
	int		start;
	int		end;
	char	*str;

	str = NULL;
	start = var->i;
	var->i++;
	while (tokens[(var->i)] && tokens[(var->i)] != '\'')
		var->i++;
	if (var->i == ft_strlen(tokens))
	{
		*join = ft_sssstrjoin(*join, ft_strdup("\'"));
		var->i = start + 1;
	}
	else
	{
		var->i++;
		end = var->i;
		str = cat_string_start_end(ft_strdup(tokens), start, end);
		*join = ft_sssstrjoin(*join, str);
	}
}
