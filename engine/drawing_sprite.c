/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utoomey <utoomey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 20:16:22 by utoomey           #+#    #+#             */
/*   Updated: 2020/09/21 17:28:00 by utoomey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

void	swap_data(t_game *data, int j)
{
	t_spr	temp_0;
	int		temp_1;
	int		temp_2;
	int		y;
	int		x;

	temp_0 = data->spr[j];
	data->spr[j] = data->spr[j + 1];
	data->spr[j + 1] = temp_0;
	y = data->spr[j].y_cell;
	x = data->spr[j].x_cell;
	temp_1 = data->matrix_spr[y * data->size_map_x + x];
	y = data->spr[j + 1].y_cell;
	x = data->spr[j + 1].x_cell;
	temp_2 = data->matrix_spr[y * data->size_map_x + x];
	data->matrix_spr[y * data->size_map_x + x] = temp_1;
	y = data->spr[j].y_cell;
	x = data->spr[j].x_cell;
	data->matrix_spr[y * data->size_map_x + x] = temp_2;
}

int		get_start_sprite(t_rays *rays, int *size, double ray)
{
	int	start;

	start = 0;
	check_angle(&ray);
	check_angle(&rays->angle_ray);
	if (ray < rays->angle_ray)
	{
		start = (int)floor((rays->angle_ray - ray)
			/ rays->angle_between);
		rays->angle_ray = ray;
	}
	else if (ray > rays->angle_ray + 180)
	{
		start = (int)floor((360 - ray + rays->angle_ray)
			/ rays->angle_between);
		rays->angle_ray = ray;
	}
	if (rays->angle_ray < ray)
	{
		*size = *size + start - (int)floor((ray - rays->angle_ray)
			/ rays->angle_between);
	}
	else
		*size += start;
	return (start);
}

double	get_offset_spr(t_rays *rays, double angle_one, double angle_two)
{
	if (angle_one > 360 && rays->angle_ray < 90)
	{
		angle_one -= 360;
		angle_two = (360 - angle_two) * -1;
	}
	else if (angle_two < 0 && rays->angle_ray > 270)
	{
		angle_one += 360;
		angle_two += 360;
	}
	return (percentage(angle_one - angle_two, angle_one - rays->angle_ray));
}

void	draw_spr(t_game *data, t_rays *rays, int i)
{
	int		start;
	int		size;
	int		is_horizontal;
	double	angle_one;
	double	angle_two;

	size = (int)floor((SIZE_BLOCK / data->spr[i].len) * (data->len_befor_pr));
	angle_two = data->spr[i].angle_ray - rays->angle_between * (size / 2);
	angle_one = data->spr[i].angle_ray + rays->angle_between * (size / 2);
	start = get_start_sprite(rays, &size, angle_one);
	while (start < data->size_x && start < size)
	{
		check_angle(&rays->angle_ray);
		write_len(data, rays, &is_horizontal);
		if (rays->len_h > data->spr[i].len)
		{
			rays->len_h = data->spr[i].len;
			rays->offset_h = get_offset_spr(rays, angle_one, angle_two);
			draw_line(data, rays, start);
		}
		rays->angle_ray -= rays->angle_between;
		rays->angle_fish -= rays->angle_between;
		start++;
	}
}

void	drawing_sprts(t_game *data, t_rays *rays)
{
	int	i;

	i = -1;
	rays->image = 4;
	sort_spr(data, data->count_spr);
	while (++i < data->count_spr)
	{
		if (data->spr[i].len != -1)
		{
			update_rays(data, rays);
			draw_spr(data, rays, i);
		}
	}
}
