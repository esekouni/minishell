/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esekouni <esekouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:56:32 by esekouni          #+#    #+#             */
/*   Updated: 2023/06/22 15:56:15 by esekouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_nnnnn(char *ch)
{
	int	i;

	i = 0;
	if (ch[i] == '-')
		i++;
	while (ch[i] && ch[i] == 'n')
		i++;
	if (ch[i] == '\0')
		return (1);
	else
		return (0);
}

static void	ft_echo_2(t_arguments *argument, char c)
{
	int			i;
	t_arguments	*args;

	args = argument;
	while (args)
	{
		i = -1;
		while (args->arg[++i])
		{
			if (args->arg[i] == '\'')
			{
				write (1, &(args->arg[i]), 1);
				while (args->arg[++i] && args->arg[i] != '\'')
					write (1, &(args->arg[i]), 1);
				write (1, &(args->arg[i]), 1);
			}
			else
				write (1, &(args->arg[i]), 1);
		}
		if (args->next && args->next->arg[0] != '\0')
			write (1, " ", 1);
		args = args->next;
	}
	if (c != '\0')
		write (1, &c, 1);
}

int	ft_echo(t_arguments *argument)
{
	t_arguments	*args;

	args = argument;
	if (!args || args->arg[0] == '\0')
	{
		write (1, "\n", 1);
		return (0);
	}
	if (check_nnnnn(args->arg) == 1)
	{
		while (args && check_nnnnn(args->arg))
			args = args->next;
		if (args)
			ft_echo_2(args, '\0');
	}
	else
		ft_echo_2(args, '\n');
	return (0);
}
