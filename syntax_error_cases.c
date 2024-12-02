/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_cases.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:00:01 by aouchaad          #+#    #+#             */
/*   Updated: 2023/06/23 14:58:46 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_out_case(char *av, int *i)
{
	if (av[*i] == '>' && av[*i + 1] != '>')
	{
		(*i)++;
		while (av[*i] == ' ' || av[*i] == '\t')
			(*i)++;
		if (av[*i] == '|' && (av[*i - 1] == ' ' || av[*i] == '\t'))
		{
			printf("minishell: syntax error\n");
			return (1);
		}
		else if (!av[*i] || av[*i] == '<')
		{
			if (!av[*i])
				printf("minishell: syntax error\n");
			else
			{
				if (av[*i + 1] && av[*i + 1] == '<')
					printf("minishell: syntax error\n");
				else
					printf("minishell: syntax error\n");
			}
			return (1);
		}
	}
	return (0);
}

static int	read_in_case(char *av, int *i)
{
	if (av[*i] == '<' && av[*i + 1] != '<')
	{
		(*i)++;
		while (av[*i] == ' ' || av[*i] == '\t')
			(*i)++;
		if (!av[*i] || av[*i] == '|' || av[*i] == '>')
		{
			if (!av[*i])
				printf("minishell: syntax error\n");
			else if (av[*i] == '>')
			{
				if (av[*i + 1] && av[*i + 1] == '>')
					printf("minishell: syntax error\n");
				else
					printf("minishell: syntax error\n");
			}
			else
				printf("minishell: syntax error\n");
			return (1);
		}
	}
	return (0);
}

static int	append_case(char *av, int *i)
{
	if (av[*i] == '>' && av[*i + 1] == '>')
	{
		*i += 2;
		while (av[*i] == ' ' || av[*i] == '\t')
			(*i)++;
		if (!av[*i] || av[*i] == '<' || av[*i] == '>' || av[*i] == '|')
		{
			if (!av[*i])
			{
				printf("minishell: syntax error\n");
				return (1);
			}
			else
			{
				if (av[*i + 1] && av[*i] == av[*i + 1])
					printf("minishell: syntax error\n");
				else
					printf("minishell: syntax error\n");
				return (1);
			}
		}
	}
	return (2);
}

static int	heredoc_case(char *av, int *i)
{
	if (av[*i] == '<' && av[*i + 1] == '<')
	{
		*i += 2;
		while (av[*i] == ' ' || av[*i] == '\t')
			(*i)++;
		if (!av[*i] || av[*i] == '<' || av[*i] == '>' || av[*i] == '|')
		{
			if (!av[*i])
			{
				printf("minishell: syntax error\n");
				return (1);
			}
			else
			{
				if (av[*i + 1] && av[*i] == av[*i + 1])
					printf("minishell: syntax error\n");
				else
					printf("minishell: syntax error\n");
				return (1);
			}
		}
	}
	return (2);
}

int	syntax_error(char *av, int i)
{
	int	j;

	if (av[i] == '|')
	{
		j = i - 1;
		i++;
		while (av[i] == ' ' || av[i] == '\t')
			i++;
		if (av[j] == '>' && (av[i] == '>' || av[i] == '<'))
		{
			printf("minishell: syntax error\n");
			return (1);
		}
		else if (!av[i] || av [i] == '|')
		{
			printf("minishell: syntax error\n");
			return (1);
		}
	}
	else if (read_in_case(av, &i) == 1 || read_out_case(av, &i) \
	== 1 || append_case(av, &i) == 1 || heredoc_case(av, &i) == 1)
		return (1);
	else if (append_case(av, &i) == 2 || heredoc_case(av, &i) == 2)
		return (2);
	return (0);
}
