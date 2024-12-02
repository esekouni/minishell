/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:13:43 by aouchaad          #+#    #+#             */
/*   Updated: 2023/06/23 15:56:34 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*command_starts_with_slash(char *command, \
			t_variables *var, char ***paths)
{
	struct stat	file_state;

	lstat(command, &file_state);
	is_der_or_isnt_reg(command, file_state);
	if (access(command, X_OK) == -1)
	{
		print_error(command, "Permission denied");
		exit (126);
	}		
	var->error = access(command, F_OK);
	if (var->error == 0)
	{
		free_double_pointer((*paths));
		return (command);
	}
	else
		print_error(command, strerror(errno));
	free_double_pointer((*paths));
	if (ft_strcmp(strerror(errno), "Not a directory") == 0)
		exit(126);
	exit(127);
	return (NULL);
}

char	*join_command_whith_pointslash(char **command_path, \
			t_variables *var, char *command, char ***paths)
{
	(*command_path) = ft_sssstrjoin(ft_strdup("./"), ft_strdup(command));
	var->error = access((*command_path), F_OK);
	if (var->error == 0)
	{
		free_double_pointer((*paths));
		return ((*command_path));
	}
	else
	{
		print_error(command, "No such file or directory");
		free_double_pointer((*paths));
		exit (127);
	}
	return (NULL);
}

char	*unset_path_case(char **command_path, \
			char *command, t_variables *var, char ***paths)
{
	(*command_path) = ft_sssstrjoin(ft_strdup("./"), ft_strdup(command));
	var->error = access((*command_path), F_OK);
	if (var->error == 0)
	{
		free_double_pointer((*paths));
		return ((*command_path));
	}
	else
	{
		print_error(command, "No such file or directory");
		exit (127);
	}
	return (NULL);
}

int	correct_path_normal_case(char **command_path, \
		t_variables *var, char *command, char ***paths)
{
	int	i;

	i = 0;
	while ((*paths) != NULL && (*paths)[i] && command != NULL)
	{
		(*command_path) = ft_sssstrjoin(ft_strdup((*paths)[i]), ft_strdup("/"));
		(*command_path) = ft_sssstrjoin((*command_path), ft_strdup(command));
		var->error = access((*command_path), F_OK);
		if (var->error == 0)
		{
			free_double_pointer((*paths));
			return (1);
		}
		free_pointer(&(*paths)[i]);
		(*paths)[i] = NULL;
		free_pointer(&(*command_path));
		i++;
	}
	return (0);
}

char	*command_path(t_environment_path *envp, char *command)
{
	char				**paths;
	char				*command_path;
	t_environment_path	*tmp;
	t_variables			var;

	tmp = envp;
	var.path_exist = 0;
	paths = NULL;
	look_for_path(&tmp, &var, &paths);
	if (command != NULL && check_caractere(command, '/') == 1)
		return (command_starts_with_slash(command, &var, &paths));
	if (tmp && tmp->variable != NULL && \
			tmp->valeur != NULL && tmp->valeur[0] == '\0')
		return (join_command_whith_pointslash(&command_path, \
											&var, command, &paths));
	if (var.path_exist == 0 && command != NULL)
		return (unset_path_case(&command_path, command, &var, &paths));
	if (correct_path_normal_case(&command_path, &var, command, &paths) == 1)
		return (command_path);
	if (command != NULL)
		print_error(command, "command not found");
	free(paths);
	paths = NULL;
	exit(127);
	return (NULL);
}
