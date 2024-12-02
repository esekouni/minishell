/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esekouni <esekouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:25:23 by esekouni          #+#    #+#             */
/*   Updated: 2023/06/22 19:39:41 by esekouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*fil_add_nprin(char	*valeur, t_variables *var)
{
	char		*str;

	str = malloc (sizeof(char) * (ft_strlen(valeur) + 1 + (var->len * 2)));
	if (!str)
		return (NULL);
	var->i = 0;
	var->j = 0;
	while (valeur && valeur[var->i] != '\0')
	{
		if (valeur[var->i] == '>' || valeur[var->i] == '<'
			|| valeur[var->i] == '\'' || valeur[var->i] == '\"'
			|| valeur[var->i] == '|')
		{
			str[var->j++] = '\x01';
			str[var->j++] = valeur[var->i++];
			str[var->j++] = '\x01';
		}
		else
			str[var->j++] = valeur[var->i++];
	}
	str[var->j] = '\0';
	return (str);
}

char	*add_nprin(char *valeur)
{
	t_variables	var;
	char		*str;

	var.i = 0;
	var.len = 0;
	while (valeur && valeur[var.i] != '\0')
	{
		if (valeur[var.i] == '>' || valeur[var.i] == '<'
			|| valeur[var.i] == '\'' || valeur[var.i] == '\"'
			|| valeur[var.i] == '|')
			var.len++;
		var.i++;
	}
	if (var.len == 0)
		return (valeur);
	str = fil_add_nprin(valeur, &var);
	free_pointer(&valeur);
	return (str);
}

int	lent_split(char **split)
{
	int	len;

	len = 0;
	while (split[len] != NULL)
		len++;
	return (len);
}
