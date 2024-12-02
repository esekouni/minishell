/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_args_and_envp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:40:11 by aouchaad          #+#    #+#             */
/*   Updated: 2023/06/23 15:09:54 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_args(char **args, t_arguments *s_args, char *command)
{
	int			i;
	t_arguments	*tmp;

	tmp = s_args;
	args[0] = command;
	i = 1;
	while (tmp)
	{
		if (tmp->arg && tmp->arg[0] != '\0')
			args[i++] = tmp->arg;
		tmp = tmp->next;
	}
	args[i] = NULL;
}

char	**join_args(char *command, t_arguments *s_args)
{
	char		**args;
	t_arguments	*tmp;
	int			arg_count;

	args = NULL;
	tmp = s_args;
	arg_count = 0;
	while (tmp)
	{
		arg_count++;
		tmp = tmp->next;
	}
	args = malloc (sizeof(char *) * (arg_count + 2));
	if (arg_count == 0)
	{
		args[0] = ft_strdup(command);
		args[1] = NULL;
		return (args);
	}
	fill_args(args, s_args, command);
	return (args);
}

void	node_counter(t_environment_path *s_envp, int *node_count)
{
	t_environment_path	*tmp;

	tmp = s_envp;
	while (tmp)
	{
		(*node_count)++;
		tmp = tmp->next;
	}
}

char	**join_envp(t_environment_path *s_envp)
{
	char				**envp;
	t_environment_path	*tmp;
	int					node_count;
	int					i;

	envp = NULL;
	tmp = s_envp;
	node_count = 0;
	node_counter(s_envp, &node_count);
	if (node_count == 0)
		return (NULL);
	envp = malloc (sizeof(char *) * (node_count + 1));
	i = 0;
	while (tmp)
	{
		envp[i] = ft_strdup(tmp->variable);
		envp[i] = ft_sssstrjoin(envp[i], ft_strdup("="));
		envp[i] = ft_sssstrjoin(envp[i], ft_strdup(tmp->valeur));
		tmp = tmp->next;
		i++;
	}	
	envp[i] = NULL;
	return (envp);
}
