/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names_generator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:33:51 by aouchaad          #+#    #+#             */
/*   Updated: 2023/06/22 15:01:50 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*names_generator(int i)
{
	return (ft_sssstrjoin(ft_strdup("/tmp/heredoc"), ft_itoa(i)));
}
