/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utoomey <utoomey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 20:16:57 by utoomey           #+#    #+#             */
/*   Updated: 2020/09/08 14:32:26 by utoomey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

int		ft_exit(t_game *data)
{
	free_data_map(data);
	exit(1);
	return (0);
}

void	handler_error(char *error, char *description, t_game *data)
{
	if (error)
		ft_putendl_fd(error, 1);
	else
	{
		ft_putendl_fd("Error:", 1);
		ft_putendl_fd(strerror(errno), 2);
	}
	if (description)
	{
		ft_putstr_fd("----> [", 1);
		ft_putstr_fd(description, 1);
		ft_putendl_fd("]", 1);
	}
	if (data)
		free_data_map(data);
	exit(1);
}
