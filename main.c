/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:58:50 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/05/04 18:29:23 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void test_print(t_gen_info *info)
{
	int i;
	printf("PATH: %s\n", info->texture_SO_path);
	printf("PATH: %s\n", info->texture_NO_path);
	printf("PATH: %s\n", info->texture_WE_path);
	printf("PATH: %s\n", info->texture_EA_path);
	printf("F:\nred:%d\nyellow:%d\nblue:%d\n", info->floor.red, info->floor.yellow, info->floor.blue);
	printf("C:\nred:%d\nyellow:%d\nblue:%d\n", info->celing.red, info->celing.yellow, info->celing.blue);
	printf("MAP: \n");
	// printf("%s", info->map[info->map_height - 1]);
	
	i = 0;
	while(info->map[i] != NULL)
	{
	printf("%s", info->map[i]);
		i++;
	}
}

int main(void)
{
	t_gen_info info;
	if (init_data_info(&info))
		test_print(&info);
	// system("leaks cube3d");
	return(0);
}