/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_identifier.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:36:36 by aouchaad          #+#    #+#             */
/*   Updated: 2023/06/22 17:45:38 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*spcs_filter(char *token)
{
	char		*str;
	t_variables	var;

	if (check_if_cotes_exist(&var, token) == 1)
		return (token);
	var.len = ft_strlen(token) - var.i;
	var.i = ft_strlen(token) - 1;
	while (var.i >= 0 && token[var.i] && token[var.i] == ' ')
	{
		var.i--;
		var.j++;
	}
	var.len -= var.j;
	str = malloc(sizeof(char) * (var.len + 1));
	if (!str)
		return (NULL);
	var.i = 0;
	var.j = 0;
	while (token[var.i] && token[var.i] == ' ')
		var.i++;
	while (token[var.i] && var.j < var.len)
		str[var.j++] = token[var.i++];
	str[var.j] = '\0';
	free_pointer(&token);
	return (str);
}

void	count_comm_and_creat_command_line(t_variables *var, \
					t_command_line **command, char **tokens)
{
	(*command) = NULL;
	var->i = 0;
	var->command_num = 1;
	while (tokens[var->i])
	{
		if (ft_strcmp(tokens[var->i], "|") == 0)
			var->command_num++;
		var->i++;
	}
	var->i = 0;
	while (var->i++ < var->command_num)
		(*command) = create_addback_commandline((*command));
}

void	fill_redirection(t_command_line **command, \
					t_variables *var, char **tokens)
{
	t_redirection	*tmpredr;

	(*command)->redirection = \
	create_addback_redirection((*command)->redirection);
	tmpredr = (*command)->redirection;
	while (tmpredr->next)
		tmpredr = tmpredr->next;
	if (ft_strcmp(tokens[var->i], "<<") == 0)
		tmpredr->file = ft_strdup(tokens[var->i + 1]);
	else
	{
		tmpredr->file = spcs_filter(ft_strdup(tokens[var->i + 1]));
		tmpredr->file = cotes_terminator(tmpredr->file);
	}
	if (ft_strcmp(tokens[var->i], "<") == 0)
		tmpredr->type = read_fromf;
	else if (ft_strcmp(tokens[var->i], ">") == 0)
		tmpredr->type = write_inf;
	else if (ft_strcmp(tokens[var->i], ">>") == 0)
		tmpredr->type = append;
	else
		tmpredr->type = heredoc;
	var->i += 2;
}

void	creat_and_fill_args(char **tokens, t_variables *var, \
									t_command_line **command)
{
	t_arguments		*tmparg;

	while (tokens[var->i] && ft_strcmp(tokens[var->i], "|") != 0)
	{
		if (ft_strcmp(tokens[var->i], "<") == 0 || ft_strcmp(tokens[var->i], \
		">") == 0 || ft_strcmp(tokens[var->i], ">>") == 0 || \
		ft_strcmp(tokens[var->i], "<<") == 0)
		{
			fill_redirection(command, var, tokens);
			break ;
		}
		else
		{
			(*command)->args = create_addback_arguemts((*command)->args);
			tmparg = (*command)->args;
			while (tmparg->next)
				tmparg = tmparg->next;
			if (check_caractere(tokens[var->i], '\x01') == 1)
				tmparg->arg = remove_non_printibale(\
				ft_strdup(tokens[var->i]), '\x01');
			else
				tmparg->arg = cotes_terminator(ft_strdup(tokens[var->i]));
		}
		var->i++;
	}
}

t_command_line	*tokens_identifier(char **tokens)
{
	t_command_line	*tmp;
	t_command_line	*command;
	t_variables		var;

	count_comm_and_creat_command_line(&var, &command, tokens);
	tmp = command;
	var.i = 0;
	while (tokens[var.i])
	{
		if (tokens[var.i] && tokens[var.i][0] != '|' && tokens[var.i][0] != '<' \
		&& tokens[var.i][0] != '>' && !command->command)
		{
			command->command = cotes_terminator(ft_strdup(tokens[var.i]));
			var.i++;
		}
		creat_and_fill_args(tokens, &var, &command);
		if (tokens[var.i] && ft_strcmp(tokens[var.i], "|") == 0)
		{
			command = command->next;
			var.i++;
		}
	}
	var.i = 0;
	command = tmp;
	return (command);
}
