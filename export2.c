/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esekouni <esekouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:38:04 by esekouni          #+#    #+#             */
/*   Updated: 2023/06/23 11:14:20 by esekouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*name_variable_export(char *split)
{
	t_variables	var;
	char		*variable;

	var.i = 0;
	var.len = 0;
	while (split[var.i] && (split[var.i] != '$'))
		var.i++;
	while (split[++var.i] && check_valid_caractr(split[var.i]) == 0)
		var.len++;
	variable = malloc(sizeof(char) * (var.len + 1));
	if (!variable)
		return (NULL);
	var.i = var.i - var.len;
	var.len = 0;
	while (split[var.i] && check_valid_caractr(split[var.i]) == 0)
		variable[var.len++] = split[var.i++];
	variable[var.len] = '\0';
	free_pointer(&split);
	return (variable);
}

int	existe_of_variable(t_environment_path *export, char *variable)
{
	t_environment_path	*tmp;
	char				*var_tmp;
	char				*tmpp ;

	tmpp = NULL;
	if (!export)
		return (0);
	if (variable[0] != '\0' && variable[0] != '$')
		tmpp = ft_sssstrjoin(ft_strdup("$"), ft_strdup(variable));
	else
		tmpp = ft_strdup(variable);
	var_tmp = name_variable_export(tmpp);
	var_tmp = ft_sssstrjoin(ft_strdup("declare -x "), var_tmp);
	tmp = export;
	while (tmp)
	{
		if (ft_strcmp(tmp->variable, var_tmp) == 0)
		{
			free_pointer(&var_tmp);
			return (1);
		}
		tmp = tmp->next;
	}
	free_pointer(&var_tmp);
	return (0);
}

int	check_syntaxe_export(char *args)
{
	int			i;

	i = 0;
	if (ft_isdigit(args[0]) == 1 || args[0] == '$' || args[0] == '=')
	{
		write(2, "minishell: export: `", 20);
		write(2, args, ft_strlen(args));
		write(2, ": not a valid identifier\n", 25);
		return (0);
	}
	while (args[i] && args[i] != '=')
	{
		if (ft_isalnum(args[i]) == 0 && args[i] != '_')
		{
			write(2, "minishell: export: `", 20);
			write(2, args, ft_strlen(args));
			write(2, ": not a valid identifier\n", 25);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_caractere(char *ch, char c)

{
	int	i;

	i = 0;
	while (ch[i] != '\0')
	{
		if (ch[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	affiche_export(t_glob *glob)
{
	t_environment_path	*export_tmp;
	int					cote;

	export_tmp = glob->export;
	while (export_tmp)
	{
		cote = 0;
		if (export_tmp->c == 1)
		{
			ft_putstr_fd(export_tmp->variable, 1);
			write(1, "=", 1);
			ft_print_valeur(export_tmp->valeur, &cote);
			write(1, "\n", 1);
		}
		else
		{
			ft_putstr_fd(export_tmp->variable, 1);
			write(1, "\n", 1);
		}
		export_tmp = export_tmp->next;
	}
}
