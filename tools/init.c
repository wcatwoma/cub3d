/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utoomey <utoomey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 20:17:04 by utoomey           #+#    #+#             */
/*   Updated: 2020/09/21 17:20:43 by utoomey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

void	init_matrix_spr(t_game *data)
{
	int		y;
	int		x;

	y = -1;
	data->size_map_x = 0;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->size_map_x < x)
				data->size_map_x = x;
		}
	}
	data->matrix_spr = (int*)malloc(sizeof(int) * data->size_map_x * y);
	if (!data->matrix_spr)
		handler_error(NULL, NULL, data);
}

void	init_texturs(t_game *data)
{
	int	i;

	i = -1;
	while (++i < 5)
	{
		if (!(data->texture[i] = (t_texture*)malloc(sizeof(t_texture))))
			handler_error(NULL, NULL, data);
		data->texture[i]->path = NULL;
		data->texture[i]->image = NULL;
		data->texture[i]->addr = NULL;
		data->texture[i]->size_x = -1;
		data->texture[i]->size_y = -1;
	}
}

t_game	*init_data_game(int is_save, int fd)
{
	t_game	*data;

	if (!(data = (t_game*)malloc(sizeof(t_game))))
		handler_error(NULL, NULL, data);
	data->mlx = (t_mlx*)malloc(sizeof(t_mlx));
	data->crd = (t_crd*)malloc(sizeof(t_crd));
	if (!data->mlx || !data->crd)
		handler_error(NULL, NULL, data);
	init_texturs(data);
	data->spr = NULL;
	data->matrix_spr = NULL;
	data->size_x = -1;
	data->size_y = -1;
	data->color_floor = NULL;
	data->color_ceiling = NULL;
	data->map = NULL;
	data->matrix_spr = NULL;
	data->is_save = is_save;
	data->mlx->mlx = NULL;
	data->mlx->window = NULL;
	data->mlx->image = NULL;
	data->line = NULL;
	data->count_spr = 0;
	data->fd = fd;
	return (data);
}
