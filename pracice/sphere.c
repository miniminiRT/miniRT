/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:28:39 by jonhan            #+#    #+#             */
/*   Updated: 2023/10/13 15:02:29 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// int	hit_sphere(t_vec3 center, double radius, t_ray r)
// {
// 	t_vec3 oc = vec3_create(r.origin.e[0] - center.e[0]
// 								,r.origin.e[1] - center.e[1]
// 								,r.origin.e[2] - center.e[2]);
// 	double a = dot_product(&(r.dir), &(r.dir));
// 	double b = 2.0 * dot_product(&oc, &(r.dir));
// 	double c = dot_product(&oc, &oc) - radius * radius;
// 	double discriminant = b * b - 4 * a * c;
// 	if (discriminant > 0)
// 		return (1);
// 	return (0);
// }

// t_vec3	ray_color(t_ray r)
// {
// 	t_vec3 color = vec3_create(255, 0, 0);
// 	t_vec3 center = vec3_create(0, 0, -1);
// 	t_vec3 no = vec3_create(0, 255, 0);
// 	if (hit_sphere(center, 0.5, r))
//     	return (color);
// 	return (no);
// }




// int	main(void)
// {
// 	t_vars	vars;
// 	t_data	image;
// 	t_ray	r;

// 	r.dir = vec3_create(1, 1, 1);
// 	r.origin = vec3_init();

// 	vars.mlx = mlx_init();
// 	vars.win = mlx_new_window(vars.mlx, 1500, 1500, "");
// 	image.img = mlx_new_image(vars.mlx, 1500, 1500);
// 	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel,
// 			&image.line_length, &image.endian);
// 	// print_width_height(image, r);
// 	// make_image(r);
// 	mlx_put_image_to_window(vars.mlx, vars.win, image.img, 0, 0);
// 	mlx_loop(vars.mlx);
// }

int convertToRGB(double r, double g, double b) {
    // 범위를 벗어나는 값들을 방지하기 위해 조정합니다.
    r = (r > 1.0) ? 1.0 : ((r < 0.0) ? 0.0 : r);
    g = (g > 1.0) ? 1.0 : ((g < 0.0) ? 0.0 : g);
    b = (b > 1.0) ? 1.0 : ((b < 0.0) ? 0.0 : b);

    // RGB 값으로 변환합니다.
    int red = (int)(r * 255.0);
    int green = (int)(g * 255.0);
    int blue = (int)(b * 255.0);

    // 하나의 RGB 값을 만듭니다.
    int rgbValue = (red << 16) | (green << 8) | blue;

    return rgbValue;
}

// void	print_width_height(t_data img, t_ray r)
// {
// 	int	i;
// 	int	j;

// 	j = 0;
// 	while (j < 1000)
// 	{
// 		i = 0;
// 		while (i < 1000 - 1)
// 		{
// 			t_vec3 color = ray_color(r);
// 			int color1 = convertToRGB(color.e[0], color.e[1], color.e[2]);
// 			my_mlx(&img, i, j, color1);
// 			printf("i: %d j: %d\n", i, j);
// 			i++;
// 		}
// 		j++;
// 	}
// 	i = 0;
// 	while (i < 1000)
// 	{
// 		j = 0;
// 		while (j < 1000 - 1)
// 		{
// 			t_vec3 color = ray_color(r);
// 			int color1 = convertToRGB(color.e[0], color.e[1], color.e[2]);
// 			my_mlx(&img, i, j, color1);
// 			j++;
// 		}
// 		i++;
// 	}
// 	printf("bye~\n");
// }

// void	make_image(t_ray r)
// {
// 	int image_width = 256;
//     int image_height = 256;

//     // Render

// 	printf("P3\n");
// 	printf("%d %d\n", image_width, image_height);
// 	printf("255\n");

//     for (int j = 0; j < image_height; ++j) {
//         for (int i = 0; i < image_width; ++i) {
// 			t_vec3 color = ray_color(r);
//             double r = color.e[0] / (image_width-1);
//             double g = color.e[0] / (image_height-1);
//             double b = 0;

//             int ir = (int)(255.999 * r);
//             int ig = (int)(255.999 * g);
//             int ib = (int)(255.999 * b);

// 			printf("%d %d %d\n", ir, ig, ib);
//         }
//     }
// }
