/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:45:13 by aouchaad          #+#    #+#             */
/*   Updated: 2023/06/23 15:38:08 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_stat = 0;

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		close(0);
		rl_catch_signals = 0;
		if (g_stat == 0)
			printf("\n");
		g_stat++;
	}
}

void	signal_call_in_main(int ac, char **av, t_variables *var)
{
	(void)ac;
	(void)av;
	var->tmp_stat = 0;
	var->token_num = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	var->fd = dup(0);
}

void	read_input(t_glob **glob, t_variables *var, char **input)
{
	if (var->tmp_stat != g_stat)
		(*glob)->exit_stat = 1;
	var->tmp_stat = g_stat;
	var->amb_red = 0;
	rl_catch_signals = 1;
	dup2(var->fd, 0);
	(*input) = readline ("minishell ~ ");
}

int	signal_cases(t_glob **glob, t_variables *var)
{
	if (rl_catch_signals == 0)
		return (1);
	else
	{
		controll_d_case(glob, var);
		return (0);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_glob		*glob;
	char		*input;
	char		**tokens;
	t_variables	var;

	glob = init_glob(envp);
	signal_call_in_main(ac, av, &var);
	while (1)
	{
		if (call_read_input(&input, &glob, &var) == 1)
			continue ;
		if (!input)
		{
			if (signal_cases(&glob, &var) == 1)
				continue ;
			else
				break ;
		}
		add_histr_check_syn(input, &var, &glob);
		if (var.error != 1)
			split_input_and_ambg(&tokens, &input, &glob);
		free_pointer(&input);
	}
	exit_fun(&var);
}
