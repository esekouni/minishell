/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:03:20 by esekouni          #+#    #+#             */
/*   Updated: 2023/06/23 16:21:41 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize_args(t_arguments *arguments)
{
	int			i;
	t_arguments	*arg;

	i = 0;
	if (!arguments)
		return (0);
	arg = arguments;
	while (arg)
	{
		i++;
		arg = arg->next;
	}
	return (i);
}

int	check_non_number(t_arguments	*arguments)
{
	t_arguments	*args;
	int			i;

	args = arguments;
	while (args)
	{
		i = 0;
		if (args->arg[i] == '-')
			i++;
		while (args->arg && i < ft_strlen(args->arg))
		{
			if (args->arg[i] && (args->arg[i] == ' '))
				i++;
			else if (args->arg[i] && ft_isdigit(args->arg[i]) == 0)
				return (0);
			i++;
		}
		args = args->next;
	}
	return (1);
}

int	check_number(char *args)
{
	int	i;

	i = 0;
	while (args && args[i])
	{
		if (ft_isdigit(args[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	no_args_case(t_glob **glob)
{
	write(2, "exit\n", 5);
	exit((*glob)->exit_stat);
}

int	ft_exit(t_arguments *args, t_glob **glob)
{
	unsigned long	exit_stat;

	if (!args)
		no_args_case(glob);
	else if (ft_lstsize_args(args) == 1 && check_non_number(args) == 1)
	{
		exit_stat = ft_atoi(args->arg);
		write(2, "exit\n", 5);
		exit(exit_stat);
	}
	else if (ft_lstsize_args(args) > 1 && check_number(args->arg) == 0)
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		(*glob)->exit_stat = 1;
		return (1);
	}
	else if (check_non_number(args) == 0)
	{
		write(2, "exit\nminishell: exit: ", 22);
		write(2, args->arg, ft_strlen(args->arg));
		write(2, ": numeric argument required\n", 28);
		exit(255);
	}
	return (0);
}
