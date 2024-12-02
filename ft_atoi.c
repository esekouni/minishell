/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 10:59:41 by esekouni          #+#    #+#             */
/*   Updated: 2023/06/23 16:16:54 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi_2(t_variables *var, char *str)
{
	var->i = 0;
	while (str[var->i] && str[var->i] >= '0' && str[var->i] <= '9')
	{
		var->v *= 10;
		var->v += str[var->i++] - '0';
		if ((var->j == -1 && var->v - 1 > LONG_MAX)
			|| (var->v > LONG_MAX && var->j == 1))
		{
			write (2, "exit\n", 5);
			write (2, "minishell: exit: ", 17);
			write(2, str, ft_strlen(str));
			write(2, ": numeric argument required\n", 28);
			return (255);
		}
	}
	return (var->v);
}

long	ft_atoi(char *str)
{
	t_variables	var;

	var.i = 0;
	var.j = 1;
	var.v = 0;
	while ((str[var.i] >= 9 && str[var.i] <= 13) || str[var.i] == 32)
		var.i++;
	if (str[var.i] == '-' || str[var.i] == '+')
	{
		if (str[var.i] == '-')
			var.j *= -1;
		var.i++;
	}
	var.v = ft_atoi_2(&var, str);
	return (var.v * var.j);
}
