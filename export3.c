/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:43:05 by esekouni          #+#    #+#             */
/*   Updated: 2023/06/23 15:03:08 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_variable_not_existe(t_glob **glob, char *args)
{
	t_environment_path	*export;
	t_environment_path	*envp;

	export = (*glob)->export;
	envp = (*glob)->envp;
	if (args[0] != '\0' && args[0] != '$')
	{
		if (check_caractere(args, '=') == 0)
		{
			(*glob)->export = ft_lstadd_back((*glob)->export,
					ft_lst_new_export(args));
			return ;
		}
		else
		{
			(*glob)->export = ft_lstadd_back((*glob)->export,
					ft_lst_new_export(args));
			(*glob)->envp = ft_lstadd_back((*glob)->envp, ft_lst_new(args));
			return ;
		}
	}
}

char	*remplace_varible_value(char *args, t_environment_path *exp)
{
	int					i;
	t_environment_path	*export;
	char				*str;

	i = 0;
	export = exp;
	if (args[0] != '$')
		str = ft_sssstrjoin(ft_strdup("$"), ft_strdup(args));
	else
		str = args;
	str = ft_sssstrjoin(ft_strdup("declare -x "), name_variable_export(str));
	while (export)
	{
		if (ft_strcmp(str, export->variable) == 0)
			break ;
		export = export->next;
	}
	free_pointer(&str);
	str = NULL;
	str = ft_sssstrjoin(str, ft_strdup(export->valeur));
	str = ft_sssstrjoin(str, ft_strchr(args, '='));
	return (str);
}

static void	add_varibale_existe_export(t_environment_path *exp,
			char *variable, char *args)
{
	t_environment_path	*export;

	export = exp;
	variable = ft_sssstrjoin(ft_strdup("declare -x "), variable);
	while (export)
	{
		if (ft_strcmp(export->variable, variable) == 0)
		{
			free_pointer(&(export->valeur));
			export->valeur = create_valeur_export(args);
			export->c = 1;
			break ;
		}
		export = export->next;
	}
	free_pointer(&variable);
}

void	add_variable_existe(t_glob **glob, char *args)
{
	t_environment_path	*envp;
	char				*variable;

	envp = (*glob)->envp;
	if (check_caractere(args, '=') == 1)
	{
		variable = ft_sssstrjoin(ft_strdup("$"), ft_strdup(args));
		variable = name_variable_export(variable);
		while (envp)
		{
			if (ft_strcmp(envp->variable, variable) == 0)
			{
				free_pointer(&(envp->valeur));
				envp->valeur = create_valeur(args);
				break ;
			}
			envp = envp->next;
		}
		add_varibale_existe_export((*glob)->export, variable, args);
	}
}
