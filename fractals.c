/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:02:59 by wlahyani          #+#    #+#             */
/*   Updated: 2022/08/09 16:08:19 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

int	calculate_iterations(t_cor p)
{
	double	temp;

	p.iteration = 0;
	while (fabsl(p.x * p.x + p.y * p.y) < 4 && p.iteration < MAX_ITER)
	{
		temp = (p.x * p.x - p.y * p.y) + p.c_r;
		p.y = (2 * p.x * p.y) + p.c_i;
		p.x = temp;
		p.iteration++;
		if (p.iteration > MAX_ITER) break;
	}	
	return (p.iteration);
}

void setup_fractal(t_fractal *frac, t_data *img)
{
    if (!ft_strncmp("M", img->t, 1)) // Mandelbrot
        frac->is_mandelbrot = 1;
    else // Julia Variants
    {
        frac->is_mandelbrot = 0;
        if (!ft_strncmp("J", img->t, 2)) 
        { frac->c_r = -0.4; frac->c_i = 0.6; }
        else if (!ft_strncmp("J1", img->t, 2)) 
        { frac->c_r = 0.28; frac->c_i = 0.008; }
        else if (!ft_strncmp("J2", img->t, 2)) 
        { frac->c_r = -0.79; frac->c_i = 0.15; }
        else if (!ft_strncmp("J3", img->t, 2)) 
        { frac->c_r = -0.162; frac->c_i = 1.04; }
    }
}
