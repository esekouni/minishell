/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sssstrjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 19:47:01 by aouchaad          #+#    #+#             */
/*   Updated: 2023/06/22 14:28:06 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_sssstrjoin(char *s1, char *s2)
{
	int		totlen;
	int		i;
	int		j;
	char	*ptr;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	totlen = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	j = 0;
	ptr = malloc(sizeof(char) * (totlen + 1));
	if (!ptr)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		ptr[i] = s1[i];
		i++;
	}
	while (i < totlen)
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	free_pointer(&s1);
	free_pointer(&s2);
	return (ptr);
}
