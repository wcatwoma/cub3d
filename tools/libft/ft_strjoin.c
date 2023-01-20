/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utoomey <utoomey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 12:32:42 by utoomey           #+#    #+#             */
/*   Updated: 2020/09/04 09:38:23 by utoomey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s)
{
	int		i;
	int		k;
	char	*new;

	if (!s1 || !s)
		return (NULL);
	i = -1;
	k = -1;
	new = (char*)malloc(sizeof(char) *
	(ft_strlen((char*)s1) + ft_strlen((char*)s) + 1));
	if (!new)
		return (NULL);
	while (*(s1 + ++i))
		*(new + i) = *(s1 + i);
	while (*(s + ++k))
		*(new + i + k) = *(s + k);
	*(new + i + k) = '\0';
	return (new);
}
