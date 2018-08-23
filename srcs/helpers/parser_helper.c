/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 14:20:22 by aabelque          #+#    #+#             */
/*   Updated: 2018/08/23 17:36:25 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			line_len(char **line)
{
	int			count;

	count = 0;
	if (!(line) || !(*line))
		return (0);
	while (line[count])
		count++;
	return (count);
}

void		clear_line(char **line)
{
	int			i;

	i = -1;
	while (line[++i])
		ft_memdel((void**)&(line[i]));
	ft_memdel((void**)&line);
}

char		**split_new_line(int fd)
{
	char		**line;
	char		**splited_content;
	int			res;

	splited_content = NULL;
	if (!(line = (char**)malloc(sizeof(char*))))
		return (NULL);
	res = get_next_line(fd, line);
	if (res == 1)
		splited_content = ft_strsplit(*line, ' ');
	ft_memdel((void**)line);
	ft_memdel((void**)(&line));
	return (splited_content);
}
