/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:49:19 by aouchaad          #+#    #+#             */
/*   Updated: 2023/06/22 15:19:27 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	func(t_variables *var, char *path, char **final_path)
{
	var->i = 0;
	var->j = 0;
	if (path[0] == ':')
	{
		(*final_path)[0] = '.';
		var->j++;
	}
	while (path[var->i])
	{
		(*final_path)[var->j++] = path[var->i];
		if (path[var->i] == ':' && path[var->i + 1] && path[var->i + 1] == ':')
			(*final_path)[var->j++] = '.';
		var->i++;
	}
	if (path[var->path_len - 1] == ':')
		(*final_path)[var->j++] = '.';
	(*final_path)[var->j] = '\0';
}

char	*path_error(char *path)
{
	char		*final_path;
	t_variables	var;

	var.path_len = ft_strlen(path);
	var.i = 0;
	var.tot_len = 0;
	if (path[0] == ':')
		var.tot_len++;
	if (path[var.path_len - 1] == ':')
		var.tot_len++;
	while (path[var.i])
	{
		if (path[var.i] == ':' && path[var.i + 1] && path[var.i + 1] == ':')
			var.tot_len++;
		var.tot_len++;
		var.i++;
	}
	final_path = malloc(sizeof(char) * (var.tot_len + 1));
	func(&var, path, &final_path);
	free_pointer(&path);
	return (final_path);
}
