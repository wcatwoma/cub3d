/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utoomey <utoomey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 12:23:20 by utoomey           #+#    #+#             */
/*   Updated: 2020/08/04 16:02:33 by utoomey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*new;

	if ((num && (size_t)~0 / num < size) ||
		(size && (size_t)~0 / size < num))
		return (NULL);
	num *= size;
	if (!(new = malloc(num)))
		return (NULL);
	ft_bzero(new, num);
	return (new);
}
