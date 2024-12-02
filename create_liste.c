/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_liste.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esekouni <esekouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:33:04 by esekouni          #+#    #+#             */
/*   Updated: 2023/06/22 12:44:20 by esekouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_commandline(t_command_line **command_line)
{
	(*command_line)->command = NULL;
	(*command_line)->args = NULL;
	(*command_line)->redirection = NULL;
	(*command_line)->next = NULL;
	(*command_line)->heredoc_fd = -1;
}

t_command_line	*create_addback_commandline(t_command_line *cmm_line)
{
	t_command_line	*command_line;
	t_command_line	*tmp;

	command_line = malloc(sizeof(t_command_line));
	if (!command_line)
		return (NULL);
	init_commandline(&command_line);
	if (!cmm_line)
		cmm_line = command_line;
	else
	{
		tmp = cmm_line;
		while (tmp)
		{
			if (tmp->next == NULL)
			{
				tmp->next = command_line;
				break ;
			}
			tmp = tmp->next;
		}
	}
	return (cmm_line);
}

t_arguments	*create_addback_arguemts(t_arguments *arguments)
{
	t_arguments	*args;
	t_arguments	*tmp;

	args = malloc(sizeof(t_arguments));
	if (!args)
		return (NULL);
	args->next = NULL;
	args->arg = NULL;
	if (!arguments)
		arguments = args;
	else
	{
		tmp = arguments;
		while (tmp)
		{
			if (tmp->next == NULL)
			{
				tmp->next = args;
				break ;
			}
			tmp = tmp->next;
		}
	}
	return (arguments);
}

t_redirection	*create_addback_redirection(t_redirection *redirection)
{
	t_redirection	*redi;
	t_redirection	*tmp;

	redi = malloc(sizeof(t_redirection));
	if (!redi)
		return (NULL);
	redi->file = NULL;
	redi->type = -1;
	redi->next = NULL;
	if (!redirection)
		redirection = redi;
	else
	{
		tmp = redirection;
		while (tmp)
		{
			if (tmp->next == NULL)
			{
				tmp->next = redi;
				break ;
			}
			tmp = tmp->next;
		}	
	}
	return (redirection);
}
