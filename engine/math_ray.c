/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utoomey <utoomey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 20:16:36 by utoomey           #+#    #+#             */
/*   Updated: 2020/09/16 19:01:33 by utoomey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

void	rounding(t_game *data, t_rays *rays, int *x, int *y)
{
	if ((rays->type || rays->angle_ray >= 180) &&
		!((rays->angle_ray >= 90 && rays->angle_ray <= 270 && rays->type)))
	{
		*x = (int)(floor(data->crd->beside_x) / (SIZE_BLOCK));
		*y = (int)(floor(data->crd->beside_y) / (SIZE_BLOCK));
	}
	else
	{
		*x = (int)(ceil(data->crd->beside_x) / (SIZE_BLOCK));
		*y = (int)(ceil(data->crd->beside_y) / (SIZE_BLOCK));
	}
}

void	write_data_spr(t_game *data, int x, int y)
{
	int i;

	i = data->matrix_spr[y * data->size_map_x + x];
	data->spr[i].leg_x = minus_if(data->crd->x >= data->spr[i].x,
									data->crd->x, data->spr[i].x);
	data->spr[i].leg_y = minus_if(data->crd->y > data->spr[i].y,
									data->crd->y, data->spr[i].y);
	data->spr[i].len = sqrt(pow(data->spr[i].leg_x, 2)
								+ pow(data->spr[i].leg_y, 2));
	data->spr[i].angle_ray = atan(data->spr[i].leg_y /
									data->spr[i].leg_x) / RADIAN;
	if (data->crd->x > data->spr[i].x
			&& data->crd->y > data->spr[i].y)
		data->spr[i].angle_ray = -1 * data->spr[i].angle_ray + 180;
	else if (data->crd->x > data->spr[i].x
			&& data->crd->y < data->spr[i].y)
		data->spr[i].angle_ray = data->spr[i].angle_ray + 180;
	else if (data->crd->x <= data->spr[i].x
			&& data->crd->y <= data->spr[i].y)
		data->spr[i].angle_ray = 360 - data->spr[i].angle_ray;
}

double	send_ray(t_game *data, t_rays *rays)
{
	int		x;
	int		y;
	double	len_x;
	double	len_y;

	first_len(data, &len_x, &len_y);
	while (1)
	{
		rounding(data, rays, &x, &y);
		if (!check_grid(data, x, y))
			return (-1);
		if (data->map[y][x] == '1')
			return (sqrt(pow(len_x, 2) + pow(len_y, 2)));
		if (data->map[y][x] == '2')
			write_data_spr(data, x, y);
		data->crd->beside_x += data->crd->step_x;
		data->crd->beside_y += data->crd->step_y;
		len_x += data->crd->step_x < 0 ?
			data->crd->step_x * -1 : data->crd->step_x;
		len_y += data->crd->step_y < 0 ?
			data->crd->step_y * -1 : data->crd->step_y;
	}
}

void	horizontal_ray(t_game *data, t_rays *rays)
{
	int	cell;

	horizontal_point(data->crd);
	rays->type = 1;
	rays->len_h = send_ray(data, rays);
	cell = (int)floor(data->crd->beside_x) / (int)SIZE_BLOCK;
	rays->offset_h = data->crd->beside_x - ((double)cell * SIZE_BLOCK);
	rays->offset_h = percentage(SIZE_BLOCK, rays->offset_h);
}

void	vertical_ray(t_game *data, t_rays *rays)
{
	int	cell;

	vertical_point(data->crd);
	rays->type = 0;
	rays->len_v = send_ray(data, rays);
	cell = (int)floor(data->crd->beside_y) / (int)SIZE_BLOCK;
	rays->offset_v = data->crd->beside_y - ((double)cell * SIZE_BLOCK);
	rays->offset_v = percentage(SIZE_BLOCK, rays->offset_v);
}
