/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:17:02 by aouchaad          #+#    #+#             */
/*   Updated: 2023/06/23 15:22:17 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_pointer(char **ptr)
{
	int	i;

	i = 0;
	if (ptr == NULL)
		return ;
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
}

void	free_varibl(t_environment_path **tmp, t_glob **glob)
{
	(*tmp) = (*glob)->export->next;
	ft_free_env(&((*glob)->export));
	(*glob)->export = (*tmp);
}

void	free_pointer(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	free_args(t_command_line **command_line, t_arguments **tmp2)
{
	free((*command_line)->args->arg);
	(*command_line)->args->arg = NULL;
	(*tmp2) = (*command_line)->args->next;
	free((*command_line)->args);
	(*command_line)->args = NULL;
	(*command_line)->args = (*tmp2);
}

void	free_command_line(t_command_line *command_line)
{
	t_redirection	*tmp1;
	t_arguments		*tmp2;

	while (command_line)
	{
		free(command_line->command);
		command_line->command = NULL;
		while (command_line->redirection)
		{
			free(command_line->redirection->file);
			command_line->redirection->file = NULL;
			tmp1 = command_line->redirection->next;
			free(command_line->redirection);
			command_line->redirection = NULL;
			command_line->redirection = tmp1;
		}
		while (command_line->args)
			free_args(&command_line, &tmp2);
		command_line = command_line->next;
	}
}
