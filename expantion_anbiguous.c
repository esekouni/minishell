/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_anbiguous.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 21:38:17 by esekouni          #+#    #+#             */
/*   Updated: 2023/06/23 15:29:39 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_glob	*init_glob(char	**envp)
{
	t_glob	*glob;

	glob = malloc(sizeof(t_glob));
	if (!glob)
		exit (1);
	glob->envp = NULL;
	glob->export = NULL;
	glob->command_line = NULL;
	glob->exit_stat = 0;
	glob->envp = init_environment_path(envp, glob->envp);
	glob->export = init_export(envp, glob->export);
	return (glob);
}

void	call_exec_free_cmmline(t_glob **glob, char ***tokens)
{
	t_command_line	*ctmp;

	(*glob)->command_line = tokens_identifier(*tokens);
	free_double_pointer(*tokens);
	here___doc(*glob);
	if (rl_catch_signals == 1)
		the_executer(glob);
	free_command_line((*glob)->command_line);
	while ((*glob)->command_line)
	{
		ctmp = (*glob)->command_line->next;
		free((*glob)->command_line);
		(*glob)->command_line = NULL;
		(*glob)->command_line = ctmp;
	}
}

int	expantion_ambiguous_redirect2(char ***tokens, t_glob **glob,
		t_variables *var)
{	
	(*tokens)[var->i] = expantion((*tokens)[var->i], *glob);
	if (ambiguous_redirect((*tokens)) == 1)
	{
		(*glob)->exit_stat = 1;
		(*glob)->amb_red = 1;
		free_double_pointer((*tokens));
		return (1);
	}
	if ((*tokens)[var->i] && (*tokens)[var->i][0] != '\0'
		&& only_spaces((*tokens)[var->i]) == 0)
	{
		(*tokens) = split_afexp((*tokens), var->i);
	}
	return (0);
}

int	expantion_ambiguous_redirect1(char ***tokens, t_glob **glob,
		t_variables *var)
{
	(*tokens)[var->i] = expantion((*tokens)[var->i], *glob);
	if (ambiguous_redirect(*tokens) == 1)
	{
		(*glob)->exit_stat = 1;
		free_double_pointer((*tokens));
		return (1);
	}
	if ((*tokens)[var->i] && (*tokens)[var->i][0] != '\0' &&
			only_spaces((*tokens)[var->i]) == 0)
	{
		(*tokens) = split_afexp((*tokens), var->i);
	}
	return (0);
}

void	expantion_ambiguous_redirect(char ***tokens, t_glob *glob)
{
	t_variables	var;

	var.i = 0;
	while (((*tokens)[var.i]))
	{
		if (var.i == 0 && (*tokens)[var.i] &&
			check_dollar(((*tokens)[var.i])) == 1)
		{
			if (expantion_ambiguous_redirect1(tokens, &glob, &var) == 1)
				break ;
		}
		else if ((*tokens)[var.i] && check_dollar(((*tokens)[var.i])) == 1
			&& (*tokens)[var.i - 1] &&
				ft_strcmp(((*tokens)[var.i - 1]), "<<") != 0)
		{
			if (expantion_ambiguous_redirect2(tokens, &glob, &var) == 1)
				break ;
		}
		var.i++;
	}
}
