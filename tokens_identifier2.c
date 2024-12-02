/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_identifier2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:44:43 by aouchaad          #+#    #+#             */
/*   Updated: 2023/06/22 17:46:03 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_cotes_exist(t_variables *var, char *token)
{
	var->i = 0;
	var->j = 0;
	var->len = 0;
	while (token[var->i])
	{
		if (token[var->i] == '\'' || token[var->i] == '\"')
			return (1);
		var->i++;
	}
	var->i = 0;
	while (token[var->i] && token[var->i] == ' ')
		var->i++;
	return (0);
}
