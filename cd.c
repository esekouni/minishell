/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esekouni <esekouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:01:45 by esekouni          #+#    #+#             */
/*   Updated: 2023/06/22 15:55:47 by esekouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	editpwd(t_glob **glob, char *path)
{
	t_environment_path	*env;
	t_environment_path	*export;

	env = (*glob)->envp;
	export = (*glob)->export;
	while (env)
	{
		if (ft_strcmp(env->variable, "PWD") == 0)
		{
			free_pointer(&(env->valeur));
			env->valeur = ft_strdup(path);
			break ;
		}
		env = env->next;
	}
	while (export)
	{
		if (ft_strcmp(export->variable, "declare -x PWD") == 0)
		{
			free_pointer(&(export->valeur));
			export->valeur = add_double_cotes(path);
			break ;
		}
		export = export->next;
	}
}

int	ftcd1(t_glob **glob)
{
	char				current_dir[PATH_MAX];
	t_environment_path	*env;

	env = (*glob)->envp;
	while (env)
	{
		if (ft_strcmp(env->variable, "HOME") == 0)
		{
			if (chdir(env->valeur) != 0)
			{
				perror("bminishell: cd:");
				return (1);
			}
			break ;
		}
		env = env->next;
	}
	if (env == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	env = (*glob)->envp;
	getcwd(current_dir, sizeof(current_dir));
	return (editpwd(glob, current_dir), 0);
}

int	ftcd2(t_glob **glob)
{
	char	current_dir[PATH_MAX];
	char	*path;

	getcwd(current_dir, sizeof(current_dir));
	path = ft_strdup((*glob)->command_line->args->arg);
	if (chdir(path) == 0)
	{
		getcwd(current_dir, sizeof(current_dir));
		editpwd(glob, current_dir);
	}
	else
	{
		write(2, "minishell: cd: ", 15);
		write(2, (*glob)->command_line->args->arg,
			ft_strlen((*glob)->command_line->args->arg));
		perror(" ");
		free_pointer(&path);
		return (1);
	}
	free_pointer(&path);
	return (0);
}

int	ftcd3(t_glob **glob)
{
	char	*path;
	char	*tmp;
	char	current_dir[PATH_MAX];

	getcwd(current_dir, sizeof(current_dir));
	tmp = ft_sssstrjoin(ft_strdup("/"),
			ft_strdup((*glob)->command_line->args->arg));
	path = ft_sssstrjoin(ft_strdup(current_dir), tmp);
	if (chdir(path) == 0)
	{
		getcwd(current_dir, sizeof(current_dir));
		editpwd(glob, current_dir);
	}
	else
	{
		write(2, "minishell: cd: ", 15);
		write(2, (*glob)->command_line->args->arg,
			ft_strlen((*glob)->command_line->args->arg));
		perror(" ");
		free_pointer(&path);
		return (1);
	}
	free_pointer(&path);
	return (0);
}

int	ft_cd(t_glob **glob)
{
	if (!(*glob)->command_line->args)
		return (ftcd1(glob));
	else if ((*glob)->command_line->args->arg[0] == '/')
		return (ftcd2(glob));
	else
		return (ftcd3(glob));
	return (0);
}
