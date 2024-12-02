/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esekouni <esekouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:13:47 by esekouni          #+#    #+#             */
/*   Updated: 2023/06/22 16:21:26 by esekouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*before_dollar(char *ch)
{
	int		i;
	char	*before;

	i = 0;
	while (ch[i] && ch[i] != '$')
		i++;
	before = malloc(sizeof(char) * (i + 1));
	if (!before)
		return (NULL);
	i = 0;
	while (ch[i] && ch[i] != '$')
	{
		before[i] = ch[i];
		i++;
	}
	before[i] = '\0';
	return (before);
}

char	*after_dollar(char *ch, t_environment_path *enp)
{
	t_variables	var;
	char		*after;

	var.i = 0;
	var.len = 0;
	(void)enp;
	while (ch[var.i] && ch[var.i] != '$')
		var.i++;
	var.i++;
	while (ch[var.i] && (ft_isalpha(ch[var.i]) == 1 || ft_isdigit(ch[var.i])))
		var.i++;
	var.j = var.i;
	while (ch[var.i] != '\0')
	{
		var.i++;
		var.len++;
	}
	after = malloc(sizeof(char) * (var.len + 1));
	if (!after)
		return (NULL);
	var.i = 0;
	while (ch[var.j] != '\0')
		after[var.i++] = ch[var.j++];
	after[var.i] = '\0';
	return (after);
}

char	*ft_strchr(char *str, char n)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != n)
		i++;
	if (str[i] == '\0')
		return (NULL);
	return (&str[i]);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char		*ch;
	size_t		l;
	int			i;
	int			j;

	i = 0;
	j = 0;
	l = ft_strlen(s1) + ft_strlen(s2);
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	ch = malloc (sizeof(char) * l + 1);
	if (ch == NULL)
		return (ch);
	while (s1 && s1[i] != '\0')
	{
		ch[i] = s1[i];
		i++;
	}
	while (s2 && s2[j] != '\0')
		ch[i++] = s2[j++];
	ch[i] = '\0';
	free_pointer(&s2);
	return (ch);
}

void	ft_free(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free_pointer(&split[i]);
		i++;
	}
	free (split);
	split = NULL;
}
