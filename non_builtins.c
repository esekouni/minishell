/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:13:54 by aouchaad          #+#    #+#             */
/*   Updated: 2023/06/23 15:57:49 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes_and_wait_for_procs(t_variables *var, \
					t_glob **glob, int **pid, int *p)
{
	var->i = 0;
	while (var->i < (var->comm_count * 2) - 2 && p != NULL)
		close(p[var->i++]);
	var->i = 0;
	while (var->i < var->comm_count)
	{
		waitpid((*pid)[var->i++], &((*glob)->exit_stat), 0);
		if ((*glob)->exit_stat == 2)
			(*glob)->exit_stat = 130;
		else if ((*glob)->exit_stat == 3)
			(*glob)->exit_stat = 131;
		else
			(*glob)->exit_stat = ((*glob)->exit_stat >> 8);
	}
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	free((*pid));
	(*pid) = NULL;
}

void	dup_to_pipe_and_execut(t_command_line **tmp, \
			t_variables *var, t_glob **glob, int *p)
{
	dup2(var->fd_in, 0);
	dup2(var->fd_out, 1);
	if ((*tmp)->command != NULL)
	{
		if (p != NULL)
		{
			if (var->i > 0 && var->rffile == 0)
				dup2(p[var->i * 2 - 2], var->fd_in);
			if (var->i < var->comm_count - 1 && var->wifile == 0)
				dup2(p[(var->i * 2) + 1], var->fd_out);
		}
		var->j = 0;
		while (var->j < (var->comm_count * 2) - 2 && p != NULL)
			close(p[var->j++]);
		builtings_in_child(glob, tmp);
		send_to_execve(glob, tmp, var);
	}
	else
		exit(0);
}

void	initial_vars(t_variables *var, int **pid, \
			t_command_line **tmp, t_glob **glob)
{
	var->i = 0;
	(*pid) = malloc (sizeof(int) * var->comm_count);
	(*tmp) = (*glob)->command_line;
}

void	signal_call_inchild(t_variables *var)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	var->fd_out = 1;
	var->fd_in = 0;
}

void	non_builtins(t_glob **glob, int command_count, int *p)
{
	t_redirection	*tmp2;
	t_command_line	*tmp;
	t_variables		var;
	int				*pid;

	var.comm_count = command_count;
	initial_vars(&var, &pid, &tmp, glob);
	signal(SIGINT, SIG_IGN);
	while (var.i < command_count && tmp)
	{
		var.rffile = 0;
		var.wifile = 0;
		pid[var.i] = fork();
		if (pid[var.i] == 0)
		{
			signal_call_inchild(&var);
			tmp2 = tmp->redirection;
			check_redirect_in_child(&var, &tmp2, &tmp);
			dup_to_pipe_and_execut(&tmp, &var, glob, p);
		}
		tmp = tmp->next;
		var.i++;
	}
	close_pipes_and_wait_for_procs(&var, glob, &pid, p);
}
