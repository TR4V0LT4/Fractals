/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:08:35 by wlahyani          #+#    #+#             */
/*   Updated: 2022/08/11 11:34:03 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

int	main(int ac, char **av)
{
	t_data	img;


	if ((ac == 2) && (!ft_strncmp("M", av[1], 2) || !ft_strncmp("J", av[1], 2)
			|| !ft_strncmp("J1", av[1], 2) || !ft_strncmp("J2", av[1], 2)
			|| !ft_strncmp("J3", av[1], 2)))
	{
        
	    img.t = av[1];
        img.scale = 1.0;
        img.x_offset = WIDTH / 2;
        img.y_offset = HEIGHT / 2;

        img.mlx = mlx_init();
        if (!img.mlx) {
            fprintf(stderr, "MLX initialization failed\n");
            return (1);
        }

        img.win = mlx_new_window(img.mlx, WIDTH, HEIGHT, "Hello");
        if (!img.win) {
            fprintf(stderr, "Window creation failed\n");
            mlx_destroy_display(img.mlx);
            return (1);
        }

        img.img = mlx_new_image(img.mlx, WIDTH, HEIGHT);
        if (!img.img) {
            fprintf(stderr, "Image creation failed\n");
            mlx_destroy_window(img.mlx, img.win);
            mlx_destroy_display(img.mlx);
            return (1);
        }

        img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
                                     &img.line_length, &img.endian);

        mlx_loop_hook(img.mlx, fill_image, &img);
        mlx_mouse_hook(img.win, zoom, &img);
        mlx_key_hook(img.win, close_win, (void *)0);
        mlx_hook(img.win, 17, 0, closex, (void *)0);
        mlx_loop(img.mlx);
	}
	else
		guide();
	return (0);
}
