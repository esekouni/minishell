/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esekouni <esekouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:13:40 by esekouni          #+#    #+#             */
/*   Updated: 2023/06/22 13:16:23 by esekouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*rm_spcs2(char *str, t_variables *var)
{
	char	*new_str;

	var->len -= var->i;
	var->i = ft_strlen(str) - 1;
	var->j = 0;
	while (str[var->i] && str[var->i] == ' ' && var->i >= 0)
	{
		var->i--;
		var->j++;
	}
	var->len -= var->j;
	new_str = malloc(sizeof(char) * (var->len + 1));
	if (!new_str)
		exit (1);
	var->i = 0;
	var->j = 0;
	while (str[var->i] && str[var->i] == ' ')
		var->i++;
	while (str[var->i] && var->j < var->len)
		new_str[var->j++] = str[var->i++];
	new_str[var->j] = '\0';
	return (new_str);
}

char	*rm_spcs(char *str)
{
	t_variables	var;
	char		*new_str;

	var.len = ft_strlen(str);
	var.i = 0;
	while (str[var.i] && str[var.i] == ' ')
		var.i++;
	if (var.i == var.len)
	{
		free_pointer(&str);
		return (ft_strdup(""));
	}
	new_str = rm_spcs2(str, &var);
	free_pointer(&str);
	return (new_str);
}

int	should_rm_spcs(char *token, int dolr_indx)
{
	if (dolr_indx > 0)
		return (0);
	dolr_indx++;
	while (token[dolr_indx])
	{
		if (ft_isalnum(token[dolr_indx]) == 0 && token[dolr_indx] != '_')
			return (0);
		dolr_indx++;
	}
	return (1);
}

char	*remove_non_printibale(char *join, char c)
{
	t_variables	var;
	char		*filtred;

	var.i = 0;
	var.j = 0;
	var.len = 0;
	while (join && join[var.i] != '\0')
	{
		if (join[var.i] != c)
			var.len++;
		var.i++;
	}
	filtred = malloc(sizeof(char) * (var.len + 1));
	if (!filtred)
		exit (1);
	var.i = 0;
	while (join && join[var.i] != '\0')
	{
		if (join[var.i] != c)
			filtred[var.j++] = join[var.i];
		var.i++;
	}
	filtred[var.j] = '\0';
	free_pointer(&join);
	return (filtred);
}
