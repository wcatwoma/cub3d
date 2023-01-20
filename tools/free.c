/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utoomey <utoomey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 22:26:23 by utoomey           #+#    #+#             */
/*   Updated: 2020/09/08 12:39:29 by utoomey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

void	ft_free(void *pointer)
{
	if (pointer)
	{
		free(pointer);
		pointer = NULL;
	}
}

void	free_texture(t_game *data)
{
	int	i;

	i = -1;
	while (++i < 5)
	{
		ft_free(data->texture[i]->path);
		if (data->mlx->image != NULL)
			mlx_destroy_image(data->mlx->mlx, data->texture[i]->image);
		ft_free(data->texture[i]);
	}
}

void	free_data_map(t_game *data)
{
	int		i;

	i = -1;
	free_texture(data);
	ft_free(data->color_floor);
	ft_free(data->color_ceiling);
	ft_free(data->crd);
	ft_free(data->spr);
	ft_free(data->matrix_spr);
	while (data->map && data->map[++i])
		ft_free(data->map[i]);
	ft_free(data->map);
	ft_free(data->line);
	close(data->fd);
	if (data->mlx->image != NULL)
		mlx_destroy_image(data->mlx->mlx, data->mlx->image);
	if (data->mlx->window != NULL)
	{
		mlx_clear_window(data->mlx->mlx, data->mlx->window);
		mlx_destroy_window(data->mlx->mlx, data->mlx->window);
	}
	ft_free(data->mlx);
	ft_free(data);
}
