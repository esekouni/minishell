/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:01:10 by aouchaad          #+#    #+#             */
/*   Updated: 2023/06/22 18:17:43 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_exp_free(t_environment_path *envp, t_environment_path *exp)
{
	t_environment_path	*tmp;

	while (envp)
	{
		free_pointer(&(envp->valeur));
		free_pointer(&(envp->variable));
		tmp = envp->next;
		free(envp);
		envp = tmp;
	}
	while (exp)
	{
		free_pointer(&(exp->valeur));
		free_pointer(&(exp->variable));
		tmp = exp->next;
		free(exp);
		exp = tmp;
	}
}

int	only_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}
