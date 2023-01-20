/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utoomey <utoomey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 12:30:37 by utoomey           #+#    #+#             */
/*   Updated: 2020/08/04 20:16:56 by utoomey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int i;

	i = -1;
	if (!s)
		return (NULL);
	while (*(s + ++i))
		if (*(s + i) == c)
			return ((char*)s + i);
	if (*(s + i) == c)
		return ((char*)s + i);
	return (NULL);
}
