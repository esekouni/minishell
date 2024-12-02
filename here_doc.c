/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:00:09 by aouchaad          #+#    #+#             */
/*   Updated: 2023/06/22 14:59:57 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expantion_here_doc(char *input, t_glob *glob)
{
	char		*join;
	t_variables	var;

	join = NULL;
	if (!input)
		return (NULL);
	if (input[0] == '\0')
		return (ft_strdup(" "));
	input = filter_dollar(input);
	var.i = 0;
	while (var.i < ft_strlen(input))
	{
		if (input[var.i] == '$')
			join = ft_sssstrjoin(join, \
			print_valeur_dollar(&input[var.i++], '\0', glob, &var));
		if (var.i < ft_strlen(input) && input[var.i] != '$')
			join_variable_with_other_value(&var, &join, input);
	}
	free_pointer(&input);
	return (join);
}

static int	check_cotes_heredoc(char *del)
{
	int	i;

	i = 0;
	if (!del)
		return (0);
	while (del[i])
	{
		if (del[i] == '\"' || del[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

void	run_herdoc(char **dl, t_variables *var, char **del, t_glob *glob)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (!input)
			break ;
		(*dl) = cotes_terminator(ft_strdup((*del)));
		if (ft_strcmp((*dl), input) == 0)
		{
			free_pointer(&input);
			break ;
		}
		if (var->cote != 1)
		{
			if (check_dollar(input) == 1)
				input = expantion_here_doc(input, glob);
		}
		write(var->fd, input, ft_strlen(input));
		write(var->fd, "\n", 1);
		free_pointer(&input);
		free_pointer(&(*dl));
	}
}

int	here_ddoc(char *del, int i, t_glob *glob)
{
	t_variables	var;
	char		*name;
	char		*dl;

	dl = NULL;
	name = names_generator(i);
	unlink(name);
	var.fd = open (name, O_CREAT | O_RDWR | O_TRUNC, 0777);
	var.cote = check_cotes_heredoc(del);
	run_herdoc(&dl, &var, &del, glob);
	close(var.fd);
	var.fd = open (name, O_CREAT | O_RDWR, 0777);
	free_pointer(&name);
	free_pointer(&dl);
	return (var.fd);
}

void	here___doc(t_glob *glob)
{
	t_command_line	*tmp;
	t_redirection	*tmp2;
	int				i;

	i = 0;
	tmp = glob->command_line;
	while (tmp)
	{
		tmp2 = tmp->redirection;
		if (tmp->redirection)
		{
			while (tmp->redirection)
			{	
				if (tmp->redirection->type == heredoc)
					tmp->heredoc_fd = here_ddoc(tmp->redirection->file, \
																i, glob);
				tmp->redirection = tmp->redirection->next;
			}
			i++;
		}
		tmp->redirection = tmp2;
		tmp = tmp->next;
	}
}
