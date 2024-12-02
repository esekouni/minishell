/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:17:31 by aouchaad          #+#    #+#             */
/*   Updated: 2023/06/23 14:55:33 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_environment_path	*ft_lstlast(t_environment_path *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

t_environment_path	*ft_lstadd_back(t_environment_path *lst,
		t_environment_path *new)
{
	t_environment_path	*l;

	if (lst == NULL)
		lst = new;
	else
	{
		l = ft_lstlast(lst);
		l->next = new;
	}
	return (lst);
}

char	*create_valeur(char *env)
{
	int		i;
	int		j;
	char	*valeur;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (i == ft_strlen(env))
		return (NULL);
	i++;
	j = i;
	while (env[i] != '\0')
		i++;
	valeur = malloc(sizeof(char) * (i - j + 2));
	if (!(valeur))
		exit (1);
	i = 0;
	while (env[j] != '\0')
		valeur[i++] = env[j++];
	valeur[i] = '\0';
	return (valeur);
}

t_environment_path	*ft_lst_new(char *ch)
{
	t_environment_path	*envi_path;
	int					i;

	i = 0;
	envi_path = malloc(sizeof(t_environment_path));
	if (!envi_path)
		return (NULL);
	while (ch[i] && ch[i] != '=')
		i++;
	envi_path->c = 0;
	if (check_caractere(ch, '=') == 1)
		envi_path->c = 1;
	envi_path->variable = malloc(sizeof(char) * (i + 1));
	if (!(envi_path->variable))
		exit (1);
	i = -1;
	while (ch[++i] && ch[i] != '=')
		envi_path->variable[i] = ch[i];
	envi_path->variable[i] = '\0';
	envi_path->valeur = create_valeur(ch);
	envi_path->next = NULL;
	return (envi_path);
}

t_environment_path	*init_environment_path(char **enp,
				t_environment_path *envi_path)
{
	int	i;

	i = 0;
	while (enp[i] != NULL)
	{
		envi_path = ft_lstadd_back(envi_path, ft_lst_new(enp[i]));
		i++;
	}
	return (envi_path);
}
