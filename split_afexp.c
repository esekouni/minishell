/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_afexp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:01:29 by aouchaad          #+#    #+#             */
/*   Updated: 2023/06/23 15:53:44 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fun(t_variables *var, int index, char ***full_str, char **strs)
{
	var->tot_len = var->strs_len + var->i;
	(*full_str) = malloc (sizeof(char *) * var->tot_len);
	if (!(*full_str))
		exit(1);
	var->j = 0;
	while (var->j < index && strs[var->j])
	{
		(*full_str)[var->j] = ft_strdup(strs[var->j]);
		var->j++;
	}
	var->i = 0;
}

char	**split_afexp(char **strs, int index)
{
	char		**tokens;
	char		**full_str;
	t_variables	var;

	strs[index] = remplace_space_nonprint(strs[index]);
	tokens = ft_split(ft_strdup(strs[index]), '\x05');
	var.i = 0;
	while (strs[var.i])
		var.i++;
	var.strs_len = var.i;
	var.i = 0;
	while (tokens[var.i])
		var.i++;
	fun(&var, index, &full_str, strs);
	while (tokens[var.i])
		full_str[var.j++] = ft_strdup(tokens[var.i++]);
	index++;
	while (strs[index])
		full_str[var.j++] = ft_strdup(strs[index++]);
	full_str[var.j] = NULL;
	free_double_pointer(strs);
	if (tokens)
		free_double_pointer(tokens);
	return (full_str);
}
