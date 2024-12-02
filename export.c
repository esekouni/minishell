/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esekouni <esekouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:07:43 by esekouni          #+#    #+#             */
/*   Updated: 2023/06/23 11:14:18 by esekouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export_argument(t_glob **glob, char *args)
{
	t_environment_path	*export;
	t_environment_path	*envp;

	envp = (*glob)->envp;
	export = (*glob)->export;
	if (check_syntaxe_export(args) == 0)
		return (1);
	if (existe_of_variable((*glob)->export, args) == 0)
		add_variable_not_existe(glob, args);
	else
		add_variable_existe(glob, args);
	return (0);
}

void	ft_print_valeur(char *valeur, int *cote)
{
	int	i;

	i = 0;
	while (valeur && valeur[i] != '\0')
	{
		if (valeur[i] == '$')
			write(1, "\\", 1);
		if (valeur[i] == '"')
		{
			if ((*cote) == 0)
				(*cote) = 1;
			else
			{
				if (valeur[i + 1] && valeur[i + 1] != '\0')
					write(1, "\\", 1);
			}
		}
		write(1, &(valeur[i]), 1);
		i++;
	}
}

char	**split_variable(char *args)
{
	char	*variable;
	char	**split;
	int		i;

	i = 0;
	while (args[i] && args[i] != '=')
		i++;
	variable = cat_string_start_end(ft_strdup(args), 0, i);
	if (check_caractere(args, '='))
	{
		split = ft_split(ft_strdup(variable), ' ');
		i = 0;
		while (split[i] && split[i + 1])
			i++;
		split[i] = ft_sssstrjoin(split[i], ft_strdup(ft_strchr(args, '=')));
	}
	else
		split = ft_split(ft_strdup(variable), ' ');
	free_pointer(&variable);
	return (split);
}

void	splite_export_argument(t_variables *var, char **split, t_glob **glob)
{
	var->i = 0;
	while (split[var->i])
	{
		if (ft_export_argument(glob, split[var->i]) == 1)
		{
			var->yes = 1;
			(*glob)->exit_stat = 1;
		}
		var->i++;
	}
}

int	ft_export(t_arguments *arguments, t_glob **glob)
{
	t_arguments	*args;
	char		**split;
	t_variables	var;

	args = arguments;
	if (!args)
		affiche_export(*glob);
	var.yes = 0;
	while (args)
	{
		split = split_variable(args->arg);
		splite_export_argument(&var, split, glob);
		free_double_pointer(split);
		if (var.yes == 0)
			(*glob)->exit_stat = 0;
		args = args->next;
	}
	return ((*glob)->exit_stat);
}
