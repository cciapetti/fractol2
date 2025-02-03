/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:11:38 by cciapett          #+#    #+#             */
/*   Updated: 2025/02/03 12:57:55 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}


int	key_hook(int key, void *arg)
{
	t_win	*program = (t_win *)arg;
	
	if (key == 65307)
	{
		mlx_destroy_image(program->mlx, program->data->img);
		mlx_clear_window(program->mlx, program->win);
		mlx_destroy_window(program->mlx, program->win);
		exit(0);
	}
	printf("%d\n", key);
	return (0);
}


int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

void	ft_colorize(int *data, bool isInside, t_count count)
{
	if (isInside == false)
		data[count.y * WIDTH + count.x] = create_trgb(count.i*10, 255/MAXITER*count.i+count.i, count.i, count.i*15);
	else
		data[count.y * WIDTH + count.x] = create_trgb(0, 0, 0, 0);
}

int	ft_iteration(t_z z, t_z c)
{
	int	i;
	t_z		z_squared;
	
	i = 0;	
	while (i < MAXITER)
	{
		z_squared.re = pow(z.re, 2);
		z_squared.im = pow(z.im, 2);
		if (z_squared.re + z_squared.im > 4)
			break ;
		double temp = z.re;
		z.re = z_squared.re - z_squared.im + c.re;
		z.im = 2*temp*z.im + c.im;
		i++;
	}
	return (i);
}

void ft_axis(t_axis *borders)
{
	borders->minre = -2.0 * borders->zoom;
	borders->maxre = 1.0 * borders->zoom;
	borders->minim= -1.2 * borders->zoom;
	borders->maxim= borders->minim+(borders->maxre-borders->minre)*HEIGHT/WIDTH * borders->zoom;
}

void	ft_displayfract(t_data	*data, t_axis *borders)
{
	t_z		z;
	t_z		c;
	t_count	count;
	bool	isInside;

	count.y = 0;
	printf("%f\n", borders->zoom);
	ft_axis(borders);
	while (count.y < HEIGHT)
	{
		count.x = 0;
		c.im = borders->maxim - count.y*((borders->maxim-borders->minim)/(HEIGHT-1));
		while (count.x < WIDTH)
		{
			c.re = borders->minre + count.x*((borders->maxre - borders->minre)/(WIDTH - 1));
			z.re = c.re;
			z.im = c.im;
			count.i = ft_iteration(z, c);
			if (count.i == MAXITER)
				isInside = true;
			else
				isInside = false;
			if ((z.re >= borders->minre &&z.re <= borders->maxre) || (z.im >= borders->minim && z.im <= borders->maxim))
				ft_colorize(data->data_pixel, isInside, count);
			count.x++;
		}
		count.y++;
	}
}

int	mouse_hook(int button, int x, int y, t_data *data)
{
	if (button == 4)
	{
		data->borders->zoom += 0.2;
		ft_displayfract(data, data->borders);
	}
	printf("%d\n", button);
	printf("%d %d\n", x, y);
	return (0);
}

int mandelbrot()
{
	t_win	program;
	t_data	im_data;
	t_axis	borders;
	
	im_data.borders = &borders;
	borders.zoom = 1;
    program.mlx = mlx_init();
    program.win = mlx_new_window(program.mlx, WIDTH, HEIGHT, "Mandelbrot fractol");
	program.data = &im_data;
	program.data->img = mlx_new_image(program.mlx, WIDTH, HEIGHT);
    im_data.data_pixel = (int *)mlx_get_data_addr(program.data->img, &im_data.bpp, &im_data.size_line, &im_data.endian);
	ft_displayfract(&im_data, &borders);
	mlx_put_image_to_window(program.mlx, program.win, program.data->img, 0, 0);
	mlx_hook(program.win, KeyPress, KeyPressMask, key_hook, &program);
	mlx_mouse_hook(program.win, mouse_hook, &program);
    mlx_loop(program.mlx);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		if (ft_strcmp(av[1], "Mandelbrot") == 0)
			mandelbrot();
		else
			printf("Invalid input: \n <Mandelbrot> \n <Julia> <value>");
	}
	else
		printf("Invalid input: \n <Mandelbrot> \n <Julia> <value>");
	return (0);
}
