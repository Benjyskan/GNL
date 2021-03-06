/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:01:15 by penzo             #+#    #+#             */
/*   Updated: 2018/11/21 09:23:20 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	int		i;
	int		s1_len;

	i = 0;
	s1_len = ft_strlen(s1);
	while (s2[i] && n > 0)
	{
		s1[s1_len + i] = s2[i];
		i++;
		n--;
	}
	s1[s1_len + i] = 0;
	return (s1);
}
