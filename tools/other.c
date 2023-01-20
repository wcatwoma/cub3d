/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utoomey <utoomey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 20:17:07 by utoomey           #+#    #+#             */
/*   Updated: 2020/09/26 14:15:40 by utoomey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

void	add_spr(t_game *data, int y, int x, int count_spr)
{
	data->spr[count_spr].x = x * SIZE_BLOCK + SIZE_BLOCK / 2;
	data->spr[count_spr].y = y * SIZE_BLOCK + SIZE_BLOCK / 2;
	data->spr[count_spr].x_cell =
		data->spr[count_spr].x / SIZE_BLOCK;
	data->spr[count_spr].y_cell =
		data->spr[count_spr].y / SIZE_BLOCK;
	data->spr[count_spr].len = -1;
	data->matrix_spr[data->size_map_x * y + x] = count_spr;
}

void	rewriting_pointer(t_game **data, int count)
{
	char	**update;
	char	**tmp;
	int		i;

	if (!(update = (char**)ft_calloc(sizeof(char*), count)))
		handler_error(NULL, NULL, *data);
	i = -1;
	while ((*data)->map[++i])
	{
		if (!(update[i] = ft_strdup((*data)->map[i])))
			handler_error(NULL, NULL, *data);
		ft_free((*data)->map[i]);
		(*data)->map[i] = NULL;
	}
	tmp = (*data)->map;
	(*data)->map = update;
	ft_free(tmp);
}

char	*skipping(const char *s, int c)
{
	int i;

	i = -1;
	if (!s)
		return (NULL);
	while (*(s + ++i))
		if (*(s + i) != c)
			return ((char*)s + i);
	return (NULL);
}
