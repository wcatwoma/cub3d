/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utoomey <utoomey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 20:16:17 by utoomey           #+#    #+#             */
/*   Updated: 2020/09/26 19:31:57 by utoomey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

void	write_len(t_game *data, t_rays *rays, int *is_horizontal)
{
	init_direction(data->crd, rays->angle_ray);
	horizontal_ray(data, rays);
	vertical_ray(data, rays);
	*is_horizontal = 1;
	if ((rays->len_v < rays->len_h && rays->len_v != -1) || rays->len_h == -1)
	{
		rays->len_h = rays->len_v;
		rays->offset_h = rays->offset_v;
		*is_horizontal = 0;
	}
}

void	write_param_drawing(t_game *data, t_rays *rays)
{
	int is_horizontal;

	write_len(data, rays, &is_horizontal);
	rays->len_h *= (ft_cos(rays->angle_fish));
	if (rays->angle_ray >= 0 && rays->angle_ray < 90)
		rays->image = is_horizontal ? 0 : 1;
	else if (rays->angle_ray >= 90 && rays->angle_ray < 180)
		rays->image = is_horizontal ? 0 : 2;
	else if (rays->angle_ray >= 180 && rays->angle_ray < 270)
		rays->image = is_horizontal ? 3 : 2;
	else if (rays->angle_ray >= 270 && rays->angle_ray < 360)
		rays->image = is_horizontal ? 3 : 1;
}

void	drawing_ceiling_floor(t_game *data)
{
	int	i;

	i = -1;
	while (++i < (data->size_y * data->size_x / 2))
	{
		(data->mlx->addr)[i] = (data->color_ceiling[0] << 16
						| data->color_ceiling[1] << 8
						| data->color_ceiling[2]);
	}
	while (++i < data->size_y * data->size_x)
	{
		(data->mlx->addr)[i] = (data->color_floor[0] << 16
						| data->color_floor[1] << 8
						| data->color_floor[2]);
	}
}

void	update_rays(t_game *data, t_rays *rays)
{
	rays->angle_ray = (data->crd->angle_direction + (FOV / 2));
	rays->angle_fish = (FOV / 2);
	rays->angle_between = FOV / (double)data->size_x;
	rays->angle_right = (data->crd->angle_direction - (FOV / 2));
	check_angle(&rays->angle_right);
}

void	drawing_walls(t_game *data, t_rays *rays)
{
	int	i;

	i = -1;
	update_rays(data, rays);
	while (++i < data->count_spr)
		data->spr[i].len = -1;
	i = -1;
	while (++i < data->size_x)
	{
		check_angle(&rays->angle_ray);
		write_param_drawing(data, rays);
		draw_line(data, rays, i);
		rays->angle_ray -= rays->angle_between;
		rays->angle_fish -= rays->angle_between;
	}
}
