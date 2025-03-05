/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 15:52:41 by wlahyani          #+#    #+#             */
/*   Updated: 2022/08/09 16:02:24 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}



void	plan_complex(t_cor *p, t_data *img)
{
    double scale_x = (4 * img->scale) / WIDTH;
    double scale_y = (4 * img->scale) / HEIGHT;

    p->r = (p->col - img->x_offset) * scale_x;
    p->i = (p->row - img->y_offset) * scale_y;
}


void	draw_fractal(t_cor *p, t_data *img)
{
    p->color = (p->iteration < MAX_ITER) ? trippy_color(p->iteration) : 0x000000;
    my_mlx_pixel_put(img, p->col, p->row, p->color);
}

int fill_image(t_data *img)
{
    pthread_t threads[NUM_THREADS];
    t_thread_data thread_data[NUM_THREADS];
    int rows_per_thread = HEIGHT / NUM_THREADS;

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_data[i].img = img;
        thread_data[i].start_row = i * rows_per_thread;
        thread_data[i].end_row = (i == NUM_THREADS - 1) ? HEIGHT : (i + 1) * rows_per_thread;
        pthread_create(&threads[i], NULL, fill_part, &thread_data[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    // Display the completed image
    mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
    return (0);
}


void *fill_part(void *arg)
{
    t_thread_data *data = (t_thread_data *)arg;
    t_cor p;
    t_fractal frac;

    setup_fractal(&frac, data->img); // Set up Mandelbrot or Julia set

    for (p.row = data->start_row; p.row < data->end_row; p.row++)
    {
        for (p.col = 0; p.col < WIDTH; p.col++)
        {
            plan_complex(&p, data->img);

            if (frac.is_mandelbrot)
            {
                p.c_r = p.r;
                p.c_i = p.i;
                p.x = 0;
                p.y = 0;
            }
            else
            {
                p.x = p.r;
                p.y = p.i;
                p.c_r = frac.c_r;
                p.c_i = frac.c_i;
            }

            p.iteration = calculate_iterations(p);
            draw_fractal(&p, data->img);
        }
    }
    return NULL;
}
