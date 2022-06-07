/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:30:59 by rschleic          #+#    #+#             */
/*   Updated: 2022/06/07 20:17:02 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	split_free(char	***tmp, char ***tmp2, t_gen_info **info, char *str)
{
	free((*tmp));
	free((*tmp2));
	error_free_exit(str, (*info), TEXTURE_PATH);
}

int	top_bottom_check(t_gen_info *info, int j)
{
	if (info->map[0][j] != '\0')
	{
		if ((info->map[0][j] != ' ' && info->map[0][j] != '1'))
			return (0);
	}
	if (info->map[info->map_y - 1][j] != '\0')
	{
		if ((info->map[info->map_y -1][j] != '1'
			&& info->map[info->map_y -1][j] != ' '))
				return (0);
	}
	return (1);
}

int	sides_check(char **info_str)
{
	int	i;
	int	j;
	int	x;
	
	i = 0;
	j = 0;
	x = 0;
	while (info_str[i] != NULL)
	{
		if (info_str[i][0] != '1' && info_str[i][0] != ' ')
			x++;
		if ((info_str[i][ft_strlen(info_str[i])-2] != '1') && (info_str[i][ft_strlen(info_str[i])-2] != ' '))
			j++;
		i++;
	}
	return (j);
}

int	check_map_valid(t_gen_info *info)
{
	int		j;

	j = 0;
	while (j < info->map_x)
	{
		if (top_bottom_check(info, j) == 0)
			return (0);
		j++;
	}
	// if (sides_check(info, ) == 0)
	// {
	// 	info->win_x = (info->map_x - 1) * 25;
	// 	info->win_y = info->map_y * 25;
	// 	return (1);
	// }
	return (1);
}

int	strcomp(char *str1, const char *str2)
{
	int	len1;
	int	len2;
	int	index;

	len1 = ft_strlen(str1);
	len2 = ft_strlen((char *)str2);
	index = 0;
	while (str1[index] == str2[index] && index <= len1)
	{
		index++;
		if (index == len2)
			return (1);
	}
	return (0);
}
