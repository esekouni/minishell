/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:30:38 by aouchaad          #+#    #+#             */
/*   Updated: 2023/06/23 15:52:20 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	controll_d_case(t_glob **glob, t_variables *var)
{
	t_command_line	*ctmp;

	var->i = 0;
	var->last_exit = (*glob)->exit_stat;
	env_exp_free((*glob)->envp, (*glob)->export);
	free_command_line((*glob)->command_line);
	while ((*glob)->command_line)
	{
		ctmp = (*glob)->command_line->next;
		free((*glob)->command_line);
		(*glob)->command_line = NULL;
		(*glob)->command_line = ctmp;
	}
	free((*glob));
	(*glob) = NULL;
}

void	split_input_and_ambg(char ***tokens, char **input, t_glob **glob)
{
	(*tokens) = giga_splite((*input));
	(*glob)->amb_red = 0;
	expantion_ambiguous_redirect(tokens, (*glob));
	if ((*glob)->amb_red == 0 && (*tokens) && (*tokens)[0] \
								&& (*tokens)[0][0] != '\0')
		call_exec_free_cmmline(glob, tokens);
}

int	call_read_input(char **input, t_glob **glob, t_variables *var)
{
	read_input(glob, var, input);
	if ((*input) && ((*input)[0] == '\0' || only_spaces((*input)) == 1))
	{
		free_pointer(&(*input));
		return (1);
	}
	return (0);
}

void	exit_fun(t_variables *var)
{
	write(1, "\nexit\n", 6);
	exit (var->last_exit);
}

void	add_histr_check_syn(char *input, t_variables *var, t_glob **glob)
{
	add_history(input);
	var->error = check_syntax(input);
	if (var->error != 0)
		(*glob)->exit_stat = 258;
}
