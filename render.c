#include "libft/libft.h"
#include "minirt.h"

void    ambient_init(t_data *data, char *line)
{
    int     i;
    char    **res;

    i = 0;
    i= i;
    data = data;
    res = NULL;
    line = line;
    // res = safe_malloc(sizeof(char *) * 2); 
    // res = ft_split_rt(line, ',');
    res = res;

}


static void	render_scene(int x, int y, t_data *data)
{
	mlx_pixel_put(&data->mlx_ptr, &data->mlx_win, x, y, BLACK);
}

int    render(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y <= data->img.height)
	{
		x = 0;
		while (x <= data->img.width)
		{
			render_scene(x, y, data);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, \
		data->img.img_ptr, 0, 0);
	return (0);
}