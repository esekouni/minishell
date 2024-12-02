/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esekouni <esekouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:00:24 by esekouni          #+#    #+#             */
/*   Updated: 2023/06/22 16:22:02 by esekouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize(t_environment_path *export)
{
	int					i;
	t_environment_path	*exp;

	i = 0;
	exp = export;
	while (exp)
	{
		i++;
		exp = exp->next;
	}
	return (i);
}

char	*add_double_cotes(char *str)
{
	int		i;
	int		len;
	char	*ch;

	i = 0;
	len = ft_strlen(str);
	ch = malloc(sizeof(char) * (len + 3));
	if (!ch)
		return (NULL);
	ch[0] = '"';
	while (str[i])
	{
		ch[i + 1] = str[i];
		i++;
	}
	ch[i + 1] = '"';
	i++;
	ch[i + 1] = '\0';
	return (ch);
}

int	check_dollar(char *ch)
{
	int	i;

	i = 0;
	while (ch && ch[i] != '\0')
	{
		if (ch[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	check_valid_caractr(char c)
{
	if (ft_isalnum(c) == 0)
	{
		if (c == '_')
			return (0);
		else
			return (1);
	}
	return (0);
}

char	*found_valeur_variable(t_environment_path *expo, char *variable)
{
	t_environment_path	*export;
	char				*valeur;

	export = expo;
	valeur = NULL;
	while (export)
	{
		if (ft_strcmp(export->variable, variable) == 0)
		{
			valeur = ft_strdup(export->valeur);
			break ;
		}
		export = export->next;
	}
	return (valeur);
}
