/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_builtins2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 23:40:33 by aouchaad          #+#    #+#             */
/*   Updated: 2023/06/23 15:14:36 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redirect_in_child(t_variables *var, t_redirection **tmp2, \
													t_command_line **tmp)
{
	while ((*tmp2))
	{
		if ((*tmp2)->type == read_fromf)
		{
			var->fd_in = check_exist_and_permission_inchild(\
								(*tmp2)->file, (*tmp2)->type);
			if (var->fd_in == -1)
				exit(1);
			var->rffile = 1;
		}
		else if ((*tmp2)->type == write_inf || (*tmp2)->type == append)
		{
			var->fd_out = check_exist_and_permission_inchild(\
								(*tmp2)->file, (*tmp2)->type);
			var->wifile = 1;
			if (var->fd_out == -1)
				exit(1);
		}
		else if ((*tmp2)->type == heredoc)
		{
			var->rffile = 1;
			var->fd_in = (*tmp)->heredoc_fd;
		}
		(*tmp2) = (*tmp2)->next;
	}
}

void	also_builtings_in_child(t_glob **glob, t_command_line **tmp)
{
	if (ft_strcmp((*tmp)->command, "exit") == 0)
	{
		(*glob)->exit_stat = ft_exit((*tmp)->args, glob);
		exit((*glob)->exit_stat);
	}
	else if (ft_strcmp((*tmp)->command, "unset") == 0)
	{
		(*glob)->exit_stat = ft_unset(glob, (*tmp)->args);
		exit((*glob)->exit_stat);
	}
	else if (ft_strcmp((*tmp)->command, "cd") == 0)
	{
		(*glob)->exit_stat = ft_cd(glob);
		exit((*glob)->exit_stat);
	}
}

void	builtings_in_child(t_glob **glob, t_command_line **tmp)
{
	if (ft_strcmp((*tmp)->command, "echo") == 0)
	{
		(*glob)->exit_stat = ft_echo((*tmp)->args);
		exit((*glob)->exit_stat);
	}
	else if (ft_strcmp((*tmp)->command, "env") == 0)
	{
		(*glob)->exit_stat = ft_env((*glob)->envp);
		exit((*glob)->exit_stat);
	}
	else if (ft_strcmp((*tmp)->command, "pwd") == 0)
	{
		(*glob)->exit_stat = ft_pwd((*glob)->envp);
		exit((*glob)->exit_stat);
	}
	else if (ft_strcmp((*tmp)->command, "export") == 0)
	{
		(*glob)->exit_stat = ft_export((*tmp)->args, glob);
		exit((*glob)->exit_stat);
	}
	also_builtings_in_child(glob, tmp);
}

void	send_to_execve(t_glob **glob, t_command_line **tmp, \
											t_variables *var)
{
	char	*path;
	char	**args;
	char	**env;

	path = command_path((*glob)->envp, (*tmp)->command);
	args = join_args((*tmp)->command, (*tmp)->args);
	env = join_envp((*glob)->envp);
	if (path != NULL && (*glob)->command_line->command != NULL)
	{
		var->error = execve(path, args, env);
		if (var->error == -1)
		{
			print_error((*glob)->command_line->command, \
										"command not found");
			exit (127);
		}
		else
			exit (0);
	}
	exit((*glob)->exit_stat);
}
