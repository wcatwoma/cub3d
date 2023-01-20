/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utoomey <utoomey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 20:16:30 by utoomey           #+#    #+#             */
/*   Updated: 2020/09/08 13:09:27 by utoomey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

double	percentage(double full, double part)
{
	return (100 * (part) / full);
}

double	ft_tan(double angle)
{
	return (tan(angle * RADIAN));
}

double	ft_cos(double angle)
{
	return (cos(angle * RADIAN));
}

double	ft_sin(double angle)
{
	return (sin(angle * RADIAN));
}
