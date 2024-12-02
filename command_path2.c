/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:23:10 by aouchaad          #+#    #+#             */
/*   Updated: 2023/06/22 14:24:08 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	look_for_path(t_environment_path **tmp, t_variables *var, char ***paths)
{
	while (*tmp)
	{
		if (ft_strcmp((*tmp)->variable, "PATH") == 0)
		{
			if ((*tmp)->valeur && (*tmp)->valeur[0] != '\0')
			{
				var->path_exist = 1;
				(*tmp)->valeur = path_error((*tmp)->valeur);
			}
			(*paths) = ft_split(ft_strdup((*tmp)->valeur), ':');
			break ;
		}
		(*tmp) = (*tmp)->next;
	}
}

void	is_der_or_isnt_reg(char *command, struct stat file_state)
{
	if (S_ISDIR(file_state.st_mode))
	{
		print_error(command, "is a directory");
		exit (126);
	}
	if (!S_ISREG(file_state.st_mode))
	{
		print_error(command, strerror(errno));
		exit (127);
	}
}
