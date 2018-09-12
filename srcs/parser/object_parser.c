#include "rtv1.h"

t_object        parse_object(int fd, t_object *object)
{
	char		**line;

    while ((line = split_new_line(fd)) && ft_strequ(line[0], "}") == FALSE)
	{
		if (line_len(line) == 4 && ft_strequ(line[0], "color"))
			object->color = color(ft_atoi(line[1]), ft_atoi(line[2]),
						ft_atoi(line[3]), 0);
        else if (line_len(line) == 4 && ft_strequ(line[0], "position"))
			object->point = point(ft_atoi(line[1]), ft_atoi(line[2]),
							ft_atoi(line[3]));
        else if (line_len(line) == 4 && ft_strequ(line[0], "point"))
			object->point = point(ft_atoi(line[1]), ft_atoi(line[2]),
					ft_atoi(line[3]));
        else if (line_len(line) == 2 && ft_strequ(line[0], "radius"))
			object->radius = ft_atoi(line[1]);
        else if (line_len(line) == 4 && ft_strequ(line[0], "center"))
			object->center = point(ft_atoi(line[1]), ft_atoi(line[2]),
					ft_atoi(line[3]));
        else if (line_len(line) == 4 && ft_strequ(line[0], "normal"))
			object->normal = normalize_vector(vector(ft_atoi(line[1]),
						ft_atoi(line[2]), ft_atoi(line[3])));
        else if (line_len(line) == 2 && ft_strequ(line[0], "pi_divider"))
			object->angle = M_PI / ft_atoi(line[1]);
        else if (line_len(line) == 4 && ft_strequ(line[0], "direction"))
			object->direction = normalize_vector(vector(ft_atoi(line[1]),
						ft_atoi(line[2]), ft_atoi(line[3])));
        else if (line_len(line) == 3 && ft_strequ(line[0], "angles"))
		{
			object->y_angle = degrees_to_radian(ft_atoi(line[1]));
			object->x_angle = degrees_to_radian(ft_atoi(line[2]));
		}
		clear_line(line);
	}
	clear_line(line);
    return (*object);
}