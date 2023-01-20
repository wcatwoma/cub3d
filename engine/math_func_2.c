/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_func_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utoomey <utoomey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 20:16:33 by utoomey           #+#    #+#             */
/*   Updated: 2020/09/08 13:08:35 by utoomey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

double	minus_if(int is_true, double one, double two)
{
	if (is_true)
		return (one - two);
	else
		return (two - one);
}

void	first_len(t_game *data, double *len_x, double *len_y)
{
	*len_x = minus_if(data->crd->field == 1 || data->crd->field == 2,
								data->crd->x, data->crd->beside_x);
	*len_y = minus_if(data->crd->field > 1,
								data->crd->beside_y, data->crd->y);
}

void	sort_spr(t_game *data, int count)
{
	int		i;
	int		j;

	i = -1;
	while (++i < count - 1)
	{
		j = -1;
		while (++j < count - i - 1)
		{
			if (data->spr[j].len < data->spr[j + 1].len)
				swap_data(data, j);
		}
	}
}
