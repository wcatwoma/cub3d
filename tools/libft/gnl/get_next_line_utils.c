/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utoomey <utoomey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 14:12:19 by utoomey           #+#    #+#             */
/*   Updated: 2020/08/04 13:44:37 by utoomey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_file	*ft_lstnew(int fd)
{
	t_file	*new;

	if (fd < 0)
		return (NULL);
	new = (t_file*)malloc(sizeof(t_file));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->tail = NULL;
	new->next = NULL;
	return (new);
}
