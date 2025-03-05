/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:30:44 by wlahyani          #+#    #+#             */
/*   Updated: 2022/08/11 11:32:14 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void	guide(void)
{
	write(1, "./fractol [M] or [J]\n", 22);
	write(1, "[M] = mandelbrot set.\n", 23);
	write(1, "[J] = julia set.\n", 18);
	write(1, "(and u can use also  J1 & J2 & J3 for more julia shapes\n)", 57);
}
