/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utoomey <utoomey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 20:16:40 by utoomey           #+#    #+#             */
/*   Updated: 2020/09/26 20:45:52 by utoomey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

int		check_grid(t_game *data, int x, int y)
{
	if (y < 0 || y > data->size_map_y)
		return (0);
	if (!data->map[y])
		return (0);
	if (x < 0 || x > ft_strlen(data->map[y]))
		return (0);
	return (1);
}

int		check_step(t_game *data, int x, int y)
{
	int		x_index;
	int		y_index;
	t_rays	rays;

	rays.angle_ray = data->crd->angle_direction;
	rounding(data, &rays, &x_index, &y_index);
	x_index = (int)floor((data->crd->x + x) / SIZE_BLOCK);
	y_index = (int)floor((data->crd->y + y) / SIZE_BLOCK);
	if (check_grid(data, data->crd->x, data->crd->y)
		|| data->map[y_index][x_index] == '1'
		|| data->map[y_index][x_index] == ' '
		|| data->map[y_index][x_index] == '\0')
		return (1);
	return (0);
}

void	edit_crd(t_game *data, double x, double y)
{
	if (data->crd->field == 1 || data->crd->field == 2)
		x *= -1;
	if (data->crd->field < 2)
		y *= -1;
	data->crd->x += x;
	data->crd->y += y;
	if (check_step(data, 10, 10) || check_step(data, -10, 10) ||
		check_step(data, 10, -10) || check_step(data, -10, -10))
	{
		data->crd->x -= x;
		data->crd->y -= y;
	}
}

void	update_crd(t_game *data, double angle)
{
	double	x;
	double	y;

	check_angle(&angle);
	init_direction(data->crd, angle);
	x = ft_cos(angle) * STEP;
	y = ft_sin(angle) * STEP;
	x = x < 0 ? x * -1 : x;
	y = y < 0 ? y * -1 : y;
	edit_crd(data, x, y);
}

int		click_button(int key, t_game *data)
{
	if (BUTTON_A == key)
		update_crd(data, data->crd->angle_direction + 90);
	else if (BUTTON_D == key)
		update_crd(data, data->crd->angle_direction - 90);
	else if (BUTTON_S == key)
		update_crd(data, data->crd->angle_direction + 180);
	else if (BUTTON_W == key)
		update_crd(data, data->crd->angle_direction);
	else if (BUTTON_ESC == key)
		ft_exit(data);
	else if (BUTTON_LEFT == key)
		data->crd->angle_direction += TURN;
	else if (BUTTON_RIGHT == key)
		data->crd->angle_direction -= TURN;
	if (BUTTON_RIGHT == key || BUTTON_LEFT == key)
		check_angle(&data->crd->angle_direction);
	render(data, 0);
	return (0);
}
