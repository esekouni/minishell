/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esekouni <esekouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:54:09 by esekouni          #+#    #+#             */
/*   Updated: 2023/06/22 13:16:29 by esekouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expantion_dollar(char **join, char *tokens,
		t_variables *var, t_glob *glob)
{
	int		do_not;
	char	*str;

	do_not = 0;
	do_not = should_rm_spcs(tokens, var->i);
	str = print_valeur_dollar(&tokens[var->i], '\0', glob, var);
	if (do_not == 1)
		str = rm_spcs(str);
	*join = ft_sssstrjoin(*join, str);
	if (var->i < ft_strlen(tokens) && tokens[var->i] != '$' \
		&& tokens[var->i] != '"' && tokens[var->i] != '\'')
		var->i++;
}

void	join_valeur_dollar(char **join, char *tokens,
		t_variables *var, t_glob *glob)
{
	char	*str;

	str = print_valeur_dollar(&tokens[var->i],
			tokens[var->i - 1], glob, var);
	*join = ft_sssstrjoin(*join, str);
	if (var->i < ft_strlen(tokens) && tokens[var->i] != '$'
		&& tokens[var->i] != '\'')
		var->i++;
}

void	expantion_double_cote(char **join, char *tokens,
		t_variables *var, t_glob *glob)
{
	char	*str;

	str = cat_string_start_end(ft_strdup(tokens), var->i, var->i + 1);
	*join = ft_sssstrjoin(*join, str);
	var->i++;
	while (tokens[(var->i)] && tokens[(var->i)] != '"')
	{
		if (tokens[var->i] == '$')
			join_valeur_dollar(join, tokens, var, glob);
		else
		{
			str = cat_string_start_end(ft_strdup(tokens), var->i, var->i + 1);
			*join = ft_sssstrjoin(*join, str);
			var->i++;
		}
	}
	if (tokens[(var->i)] == '"')
	{
		str = cat_string_start_end(ft_strdup(tokens), var->i, var->i + 1);
		*join = ft_sssstrjoin(*join, str);
		var->i++;
	}
}

void	expantion_caracter(char *tokens, char **join, t_variables *var)
{
	char	*str;

	str = NULL;
	var->j = var->i;
	while (tokens[(var->i)] && tokens[(var->i)] != '\''
		&& tokens[(var->i)] != '$' && tokens[(var->i)] != '"')
		var->i++;
	str = cat_string_start_end(ft_strdup(tokens), var->j, var->i);
	*join = ft_sssstrjoin(*join, str);
}

char	*expantion(char *tokens, t_glob *glob)
{
	t_variables	var;
	char		*join;

	if (!tokens)
		return (ft_strdup(""));
	var.i = 0;
	join = NULL;
	tokens = filter_dollar(tokens);
	if (tokens[0] == '\0')
		return (ft_strdup(" "));
	while (tokens[(var.i)] && var.i != ft_strlen(tokens))
	{
		if (tokens[(var.i)] == '\'')
			expantion_single_cote(&join, tokens, &var);
		else if (tokens[(var.i)] == '"')
			expantion_double_cote(&join, tokens, &var, glob);
		else if (tokens[(var.i)] == '$')
			expantion_dollar(&join, tokens, &var, glob);
		if (tokens[var.i] && tokens[(var.i)] != '\''
			&& tokens[(var.i)] != '$' && tokens[(var.i)] != '"')
			expantion_caracter(tokens, &join, &var);
	}
	free_pointer(&tokens);
	join = remove_non_printibale(join, '\x07');
	return (join);
}
