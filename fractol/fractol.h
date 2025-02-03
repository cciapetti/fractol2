/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:34:38 by cciapett          #+#    #+#             */
/*   Updated: 2025/02/03 12:01:39 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include "minilibx-linux/mlx_int.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <math.h>
#include <stdbool.h>

#define WIDTH 800
#define HEIGHT 600
#define MINRE -2.0
#define MAXRE 1.0
#define MINIM -1.2
#define MAXITER	10
#define MAXIM MINIM+(MAXRE-MINRE)*HEIGHT/WIDTH

typedef struct s_axis
{
	double zoom;
	double minre;
	double maxre;
	double minim;
	double maxim;
}	t_axis;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		*data_pixel;
	t_axis	*borders;
}				t_data;

typedef struct	s_win {
	void	*mlx;
	void	*win;
	t_data    *data;
} t_win;

typedef struct	s_z {
	double	re;
	double	im;
} t_z;

typedef struct	s_count {
	int	x;
	int	y;
	int	i;
} t_count;