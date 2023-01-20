/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utoomey <utoomey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 20:16:45 by utoomey           #+#    #+#             */
/*   Updated: 2020/09/26 18:46:16 by utoomey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

void	load_image(t_game *data)
{
	int	i;

	i = -1;
	while (++i < 5)
	{
		data->texture[i]->image =
				(int*)mlx_xpm_file_to_image(data->mlx->mlx,
				data->texture[i]->path, &data->texture[i]->size_x,
				&data->texture[i]->size_y);
		data->texture[i]->addr =
				(int*)mlx_get_data_addr(data->texture[i]->image,
				&data->texture[i]->bpp, &data->texture[i]->size_line,
				&data->texture[i]->endian);
	}
}

void	render(t_game *data, int is_screen)
{
	t_rays	rays;

	data->mlx->image = mlx_new_image(data->mlx->mlx,
		data->size_x, data->size_y);
	data->mlx->addr = (int*)mlx_get_data_addr(data->mlx->image,
		&data->mlx->bpp, &data->mlx->size_line, &data->mlx->endian);
	drawing_ceiling_floor(data);
	drawing_walls(data, &rays);
	drawing_sprts(data, &rays);
	mlx_put_image_to_window(data->mlx->mlx,
		data->mlx->window, data->mlx->image, 0, 0);
	if (!is_screen)
	{
		mlx_destroy_image(data->mlx->mlx, data->mlx->image);
		data->mlx->image = NULL;
	}
}

void	run_game(t_game *data, int is_screen)
{
	int		size_x;
	int		size_y;

	data->mlx->mlx = mlx_init();
	mlx_get_screen_size(data->mlx->mlx, &size_x, &size_y);
	data->size_x = data->size_x > size_x ? size_x : data->size_x;
	data->size_y = data->size_y > size_y ? size_y : data->size_y;
	data->mlx->window = mlx_new_window(data->mlx->mlx, data->size_x,
		data->size_y, "Title");
	load_image(data);
	data->len_befor_pr = (data->size_x / 2) / ft_tan(FOV / 2);
	render(data, is_screen);
	if (is_screen)
	{
		save_screen(data);
		return ;
	}
	mlx_hook(data->mlx->window, 2, 1L << 0, click_button, data);
	mlx_hook(data->mlx->window, 17, 1L << 17, ft_exit, data);
	mlx_loop(data->mlx->mlx);
}
