/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utoomey <utoomey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 20:16:10 by utoomey           #+#    #+#             */
/*   Updated: 2020/09/26 20:45:39 by utoomey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

int		get_color_pixel(t_game *data, t_rays *rays, double step)
{
	int		y;
	int		x;
	int		size;

	size = data->texture[rays->image]->size_x;
	y = (int)floor(step) * size;
	x = (int)floor((rays->offset_h * (double)size) / 100.0);
	y = y < 0 ? 0 : y;
	x = x < 0 ? 0 : x;
	return (data->texture[rays->image]->addr[y + x]);
}

void	draw_line(t_game *data, t_rays *rays, int i)
{
	int		start;
	int		len_line;
	int		color;
	double	step;
	double	y_step;

	len_line = (int)floor((SIZE_BLOCK / rays->len_h) * data->len_befor_pr);
	start = (int)floor((double)((data->size_y / 2) - ((int)len_line / 2)));
	step = (double)data->texture[rays->image]->size_y / (double)len_line;
	y_step = 0.0;
	if (start < 0)
	{
		len_line += start;
		y_step += step * (start * -1);
		start = 0;
	}
	len_line = len_line >= data->size_y ? data->size_y : len_line;
	while (len_line-- > 0)
	{
		color = get_color_pixel(data, rays, y_step);
		if (color >= 0 && color <= 16777215)
			((data->mlx->addr))[start * data->size_x + i] = color;
		start++;
		y_step += step;
	}
}
