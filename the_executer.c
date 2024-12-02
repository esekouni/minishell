/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_executer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:32:14 by aouchaad          #+#    #+#             */
/*   Updated: 2023/06/23 15:12:18 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_var(t_variables *var, t_command_line **tmp2, \
							t_redirection **tmp1, int **p)
{
	(*p) = NULL;
	var->i = 0;
	var->fd_out = 1;
	var->comm_count = 0;
	var->error = 0;
	(*tmp1) = (*tmp2)->redirection;
	while ((*tmp2))
	{
		var->comm_count++;
		(*tmp2) = (*tmp2)->next;
	}
	if (var->comm_count > 1)
		(*p) = malloc (sizeof(int) * (var->comm_count - 1) * 2);
}

void	pipe_creation(t_variables *var, int **p)
{
	while (var->i < var->comm_count - 1)
	{
		if (pipe((*p) + (var->i * 2)) == -1)
		{
			perror("pipe: ");
			exit (1);
		}
		var->i++;
	}
}

int	check_redirection(t_redirection **tmp1, t_variables *var, \
										int **p, t_glob **glob)
{
	if ((*tmp1)->type == read_fromf)
	{
		var->error = check_exist_and_permission((*tmp1)->file, (*tmp1)->type);
		if (var->error == -1)
		{
			free((*p));
			(*p) = NULL;
			(*glob)->exit_stat = 1;
			return (1);
		}
	}
	else if ((*tmp1)->type == write_inf || (*tmp1)->type == append)
	{
		var->fd_out = check_exist_and_permission((*tmp1)->file, (*tmp1)->type);
		if (var->fd_out == -1)
		{
			free((*p));
			(*p) = NULL;
			(*glob)->exit_stat = 1;
			return (1);
		}
	}
	(*tmp1) = (*tmp1)->next;
	return (0);
}

void	builtins(t_variables *var, t_glob **glob, int *p)
{
	if (var->fd_out != 1)
		close(var->fd_out);
	if (ft_strcmp((*glob)->command_line->command, "echo") == 0)
		(*glob)->exit_stat = ft_echo((*glob)->command_line->args);
	else if (ft_strcmp((*glob)->command_line->command, "env") == 0)
		(*glob)->exit_stat = ft_env((*glob)->envp);
	else if (ft_strcmp((*glob)->command_line->command, "pwd") == 0)
		(*glob)->exit_stat = ft_pwd((*glob)->envp);
	else if (ft_strcmp((*glob)->command_line->command, "export") == 0)
		(*glob)->exit_stat = ft_export((*glob)->command_line->args, glob);
	else if (ft_strcmp((*glob)->command_line->command, "exit") == 0)
		(*glob)->exit_stat = ft_exit((*glob)->command_line->args, glob);
	else if (ft_strcmp((*glob)->command_line->command, "unset") == 0)
		(*glob)->exit_stat = ft_unset(glob, (*glob)->command_line->args);
	else if (ft_strcmp((*glob)->command_line->command, "cd") == 0)
		(*glob)->exit_stat = ft_cd(glob);
	else
		non_builtins(glob, var->comm_count, p);
}

void	the_executer(t_glob **glob)
{
	int				*p;
	t_command_line	*tmp2;
	t_redirection	*tmp1;
	t_variables		var;

	tmp2 = (*glob)->command_line;
	init_var(&var, &tmp2, &tmp1, &p);
	if (p != NULL)
		pipe_creation(&var, &p);
	if (var.comm_count == 1)
	{
		while (tmp1)
		{
			if (check_redirection(&tmp1, &var, &p, glob) == 1)
				return ;
		}
		var.g = dup(1);
		dup2(var.fd_out, 1);
		builtins(&var, glob, p);
		dup2(var.g, 1);
	}
	else
		non_builtins(glob, var.comm_count, p);
	free(p);
	p = NULL;
}
