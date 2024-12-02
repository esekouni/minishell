/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:04:23 by esekouni          #+#    #+#             */
/*   Updated: 2023/06/23 15:53:16 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_environment_path *envp)
{
	t_environment_path	*env;
	char				current_dir[PATH_MAX];

	env = envp;
	getcwd(current_dir, sizeof(current_dir));
	ft_putstr_fd(current_dir, 1);
	write (1, "\n", 1);
	return (0);
}
