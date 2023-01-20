/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utoomey <utoomey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 22:21:29 by utoomey           #+#    #+#             */
/*   Updated: 2020/09/26 20:44:24 by utoomey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

void	check_angle(double *angle)
{
	if (*angle >= 360)
		*angle -= 360;
	else if (*angle < 0)
		*angle += 360;
}

void	check_rgb(t_game *data, int **color, int count_comma, int flag)
{
	if ((*color)[0] < 0 || (*color)[0] > 255 || (*color)[1] < 0 ||
		(*color)[1] > 255 || (*color)[2] < 0 || (*color)[2] > 255 ||
		count_comma != 2 || flag)
		handler_error("Error:\nnot valid rgb code!", data->line, data);
}

int		check_data(t_game *data, int code_test, int i, int k)
{
	if (code_test == 1)
	{
		if (!data->map || data->size_x == -1 || data->size_y == -1 ||
			!data->texture[0]->path || !data->texture[1]->path ||
			!data->texture[2]->path || !data->texture[3]->path ||
			!data->texture[4]->path || !data->color_floor ||
			!data->color_ceiling)
			return (1);
	}
	else if (code_test == 2)
	{
		if (!check_grid(data, k, i - 1) || !check_grid(data, k - 1, i)
			|| !check_grid(data, k, i + 1) || !check_grid(data, k + 1, i))
			return (1);
		if (((i > 0 && ft_strchr(" ", data->map[i - 1][k]) != NULL) ||
			(k > 0 && ft_strchr(" ", data->map[i][k - 1]) != NULL))
			|| (ft_strchr(" ", data->map[i + 1][k]) != NULL) ||
			(ft_strchr(" ", data->map[i][k + 1]) != NULL))
			return (1);
	}
	return (0);
}

void	check_point(t_game *data, int y, int x, int *count_point)
{
	if (ft_strchr("NEWS", data->map[y][x]))
	{
		if (data->map[y][x] == 'N')
			data->crd->angle_direction = 90.0;
		else if (data->map[y][x] == 'E')
			data->crd->angle_direction = 0.0;
		else if (data->map[y][x] == 'W')
			data->crd->angle_direction = 180.0;
		else if (data->map[y][x] == 'S')
			data->crd->angle_direction = 270.0;
		data->crd->x = ((double)x * SIZE_BLOCK) + (SIZE_BLOCK / 2) + 0.003;
		data->crd->y = ((double)y * SIZE_BLOCK) + (SIZE_BLOCK / 2) + 0.003;
		(*count_point)++;
	}
	if (!ft_strchr(" 012NEWS", data->map[y][x]))
		handler_error("Error:\nincorrect symbols in the map!",
			data->map[y], data);
	if (ft_strchr("02NEWS", data->map[y][x]) && check_data(data, 2, y, x))
		handler_error("Error:\nthere is no full wall in the map!",
			data->map[y], data);
}

void	check_map(t_game *data)
{
	int		count_point_start;
	int		count_spr;
	int		y;
	int		x;

	count_point_start = 0;
	count_spr = 0;
	y = -1;
	init_matrix_spr(data);
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			data->size_map_y = y + 1;
			check_point(data, y, x, &count_point_start);
			if (data->map[y][x] == '2')
				add_spr(data, y, x, count_spr++);
		}
	}
	if (y < 2 && ft_strlen(data->map[1]) < 3)
		handler_error("Error:\nThe map is too small!", NULL, data);
	if (count_point_start != 1)
		handler_error("Error:\nmany starting points!", NULL, data);
}
