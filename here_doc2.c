/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:59:35 by aouchaad          #+#    #+#             */
/*   Updated: 2023/06/22 15:01:00 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expantion_caracter_heredoc(char *tokens, char **join, t_variables *var)
{
	var->j = var->i;
	while (var->i < ft_strlen(tokens) && tokens[(var->i)] != '$')
		var->i++;
	*join = ft_sssstrjoin(*join, \
	cat_string_start_end(ft_strdup(tokens), var->j, var->i));
}

void	join_variable_with_other_value(t_variables *var, \
								char **join, char *input)
{
	var->j = var->i;
	while (var->i < ft_strlen(input) && input[(var->i)] != '$')
		var->i += 1;
	(*join) = ft_sssstrjoin((*join), \
	cat_string_start_end(ft_strdup(input), var->j, var->i));
}
