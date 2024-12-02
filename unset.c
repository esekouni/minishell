/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:17:36 by esekouni          #+#    #+#             */
/*   Updated: 2023/06/23 15:22:31 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env(t_environment_path **env)
{
	free((*env)->valeur);
	(*env)->valeur = NULL;
	free((*env)->variable);
	(*env)->variable = NULL;
	free((*env));
	(*env) = NULL;
}

void	ft_unset_export(t_glob **glob, char *variable)
{
	t_environment_path	*ex;
	t_environment_path	*tmp;

	ex = (*glob)->export;
	variable = ft_sssstrjoin(ft_strdup("declare -x "), variable);
	if (ft_strcmp(ex->variable, variable) == 0)
		free_varibl(&tmp, glob);
	else
	{
		while (ex->next)
		{
			tmp = ex;
			ex = ex->next;
			if (ft_strcmp(ex->variable, variable) == 0)
			{
				tmp->next = ex->next;
				ft_free_env(&ex);
				break ;
			}
		}
	}
	free_pointer(&variable);
}

void	ft_unset_env(t_glob **glob, char *variable)
{
	t_environment_path	*en;
	t_environment_path	*tmp;

	en = (*glob)->envp;
	if (ft_strcmp((*glob)->envp->variable, variable) == 0)
	{
		tmp = (*glob)->envp->next;
		ft_free_env((&(*glob)->envp));
		(*glob)->envp = tmp;
	}
	else
	{
		while (en->next)
		{
			tmp = en;
			en = en->next;
			if (ft_strcmp(en->variable, variable) == 0)
			{
				tmp->next = en->next;
				ft_free_env(&en);
				break ;
			}
		}
	}
}

int	check_args_unset(char *args, t_glob *glob)
{
	int			i;

	i = 0;
	if (ft_isdigit(args[i]) == 1 || args[i] == '$' || args[i] == '=')
	{
		write(2, "minishell: export: `", 20);
		write(2, args, ft_strlen(args));
		write(2, ": not a valid identifier\n", 25);
		glob->exit_stat = 1;
		return (0);
	}
	while (args[i])
	{
		if (ft_isalnum(args[i]) == 0 && args[i] != '_')
		{
			write(2, "minishell: export: `", 20);
			write(2, args, ft_strlen(args));
			write(2, ": not a valid identifier\n", 25);
			glob->exit_stat = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_unset(t_glob **glob, t_arguments *arguments)
{
	char		*variable;
	t_arguments	*args;

	variable = NULL;
	args = arguments;
	while (args)
	{
		if (ft_lstsize((*glob)->export) == 0)
			return (0);
		if (check_args_unset(args->arg, *glob) == 0)
			return (1);
		ft_unset_env(glob, args->arg);
		ft_unset_export(glob, ft_strdup(args->arg));
		args = args->next;
	}
	return (0);
}
