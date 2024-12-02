/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:47:18 by esekouni          #+#    #+#             */
/*   Updated: 2023/06/23 15:56:27 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_valeur_export(char *env)
{
	t_variables	var;
	char		*valeur;

	var.i = 0;
	while (env[var.i] && env[var.i] != '=')
		var.i++;
	if (var.i == ft_strlen(env))
		return (ft_strdup("\"\""));
	var.i++;
	var.j = var.i;
	while (env[var.i] != '\0')
		var.i++;
	valeur = malloc(sizeof(char) * (var.i - var.j + 3));
	if (!valeur)
		exit(1);
	var.i = 1;
	valeur[0] = '"';
	while (env[var.j] != '\0')
		valeur[var.i++] = env[var.j++];
	valeur[var.i++] = '"';
	valeur[var.i] = '\0';
	return (valeur);
}

t_environment_path	*ft_lst_new_export(char *enp)
{
	t_environment_path	*export;
	int					i;

	i = 0;
	export = malloc(sizeof(t_environment_path));
	if (!export)
		return (NULL);
	while (enp[i] && enp[i] != '=')
		i++;
	export->variable = malloc(sizeof(char) * (i + 1));
	if (!export->variable)
		exit(1);
	i = -1;
	while (enp[++i] && enp[i] != '=')
		export->variable[i] = enp[i];
	export->c = 0;
	if (check_caractere(enp, '=') == 1)
		export->c = 1;
	export->variable[i] = '\0';
	export->variable = ft_sssstrjoin(ft_strdup("declare -x "),
			export->variable);
	export->valeur = create_valeur_export(enp);
	export->next = NULL;
	return (export);
}

t_environment_path	*init_export(char **enp,
				t_environment_path *export)
{
	int	i;

	i = 0;
	while (enp[i] != NULL)
	{
		export = ft_lstadd_back(export, ft_lst_new_export(enp[i]));
		i++;
	}
	return (export);
}
