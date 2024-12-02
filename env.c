/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esekouni <esekouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:08:05 by esekouni          #+#    #+#             */
/*   Updated: 2023/06/22 12:51:21 by esekouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_environment_path *env)
{
	t_environment_path	*envp;

	if (!env)
	{
		ft_putstr_fd("minishell: env: No such file or directory\n", 2);
		return (127);
	}
	envp = env;
	while (envp)
	{
		ft_putstr_fd(envp->variable, 1);
		write(1, "=", 1);
		ft_putstr_fd(envp->valeur, 1);
		write(1, "\n", 1);
		envp = envp->next;
	}
	return (0);
}
