/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utoomey <utoomey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 20:16:50 by utoomey           #+#    #+#             */
/*   Updated: 2020/09/08 13:03:37 by utoomey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

void	write_pixel(int num, unsigned char *arr)
{
	arr[0] = (unsigned char)(num & 255);
	arr[1] = (unsigned char)((num >> 8) & 255);
	arr[2] = (unsigned char)((num >> 16) & 255);
	arr[3] = (unsigned char)((num >> 24) & 255);
}

void	write_header(t_game *data, unsigned char *bytes, int bmpsize)
{
	int			pixels_per_meter;

	bytes[0] = 'B';
	bytes[1] = 'M';
	write_pixel(bmpsize, bytes + 2);
	bytes[10] = (unsigned char)54;
	bytes[14] = (unsigned char)40;
	write_pixel(data->size_x, bytes + 18);
	write_pixel(data->size_y, bytes + 22);
	bytes[26] = (unsigned char)1;
	bytes[28] = (unsigned char)32;
	bytes[34] = (unsigned char)32;
	pixels_per_meter = (int)((double)70 * 39.37);
	write_pixel(pixels_per_meter, bytes + 38);
	write_pixel(pixels_per_meter, bytes + 42);
}

void	write_image(t_game *data, unsigned char *bytes, int bmpsize)
{
	int		i;
	int		x;
	int		y;

	i = 54;
	y = data->size_y;
	while (y-- > 0)
	{
		x = -1;
		while (++x < data->size_x && i < bmpsize)
		{
			write_pixel(data->mlx->addr[y * data->size_x + x], bytes + i);
			i += 4;
		}
	}
	mlx_destroy_image(data->mlx->mlx, data->mlx->image);
	data->mlx->image = NULL;
}

void	save_screen(t_game *data)
{
	int				file;
	int				size;
	unsigned char	*bytes;

	file = open("./screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (file < 0)
		handler_error(NULL, NULL, data);
	size = data->size_x * data->size_y * 4 + 54;
	if (!(bytes = (unsigned char *)malloc(sizeof(unsigned char) * size)))
		handler_error(NULL, NULL, data);
	write_header(data, bytes, size);
	write_image(data, bytes, size);
	if (write(file, bytes, size) < size)
	{
		free(bytes);
		close(file);
		handler_error("Failed to write screenshot file!", NULL, data);
	}
	free(bytes);
	close(file);
	ft_putendl_fd("Screenshot saved to ./screenshot.bmp", 1);
	ft_exit(data);
}
