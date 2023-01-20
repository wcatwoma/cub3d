/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_field.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utoomey <utoomey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 20:16:27 by utoomey           #+#    #+#             */
/*   Updated: 2020/09/08 13:10:27 by utoomey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

void	init_direction(t_crd *crd, double angle_ray)
{
	if (angle_ray < 90)
	{
		crd->angle = angle_ray;
		crd->field = 0;
	}
	else if (angle_ray < 180)
	{
		crd->angle = 180 - angle_ray;
		crd->field = 1;
	}
	else if (angle_ray < 270)
	{
		crd->angle = angle_ray - 180;
		crd->field = 2;
	}
	else if (angle_ray < 360)
	{
		crd->angle = 360 - angle_ray;
		crd->field = 3;
	}
}

void	init_sign(t_crd *crd, int type)
{
	if (type)
	{
		crd->correction = crd->field > 1 ? SIZE_BLOCK : -1;
		crd->sign_direction =
			crd->field == 1 || crd->field == 2 ? -1 : 1;
	}
	else
	{
		crd->correction =
			crd->field == 1 || crd->field == 2 ? -1 : SIZE_BLOCK;
		crd->sign_direction = crd->field > 1 ? 1 : -1;
	}
	crd->sign_y = crd->field > 1 ? 1 : -1;
	crd->sign_x = crd->field == 1 || crd->field == 2 ? -1 : 1;
}

void	horizontal_point(t_crd *crd)
{
	init_sign(crd, 1);
	crd->beside_y = floor(crd->y / SIZE_BLOCK) * SIZE_BLOCK;
	crd->beside_y += crd->correction;
	crd->beside_x = minus_if(crd->correction == -1, crd->y, crd->beside_y);
	crd->beside_x /= ft_tan(crd->angle);
	crd->beside_x *= crd->sign_direction;
	crd->beside_x = (crd->beside_x);
	crd->beside_x += crd->x;
	crd->step_y = SIZE_BLOCK * crd->sign_y;
	crd->step_x = (SIZE_BLOCK / ft_tan(crd->angle)) * (double)crd->sign_x;
}

void	vertical_point(t_crd *crd)
{
	init_sign(crd, 0);
	crd->beside_x = floor(crd->x / SIZE_BLOCK) * SIZE_BLOCK;
	crd->beside_x += crd->correction;
	crd->beside_y = minus_if(crd->correction == -1, crd->x, crd->beside_x);
	crd->beside_y *= ft_tan(crd->angle);
	crd->beside_y *= crd->sign_direction;
	crd->beside_y = (crd->beside_y);
	crd->beside_y += crd->y;
	crd->step_x = SIZE_BLOCK * crd->sign_x;
	crd->step_y = (SIZE_BLOCK * ft_tan(crd->angle)) * crd->sign_y;
}
