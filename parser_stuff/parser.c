
#include "../cub3d.h"

int map_parse_condition(t_gen_info *info, int i)
{
	if (info->info_string[i][0] == ' '
		|| info->info_string[i][0] == '0'
		|| info->info_string[i][0] == '1')
	{
		return (1);
	}
	return (0);
}
//hier könte man die 0 gleich weg lassen?
//da am Anfnag ja nur leer oder 1 sein darf?

int	parse_color_settings(char *str, t_gen_info *info)
{
	if (!ft_strncmp(str, "F ", ft_strlen("F ")))
	{
		if (!split_values(str, info))
			return (0);
		return (1);
	}
	else if (!ft_strncmp(str, "C ", ft_strlen("C ")))
	{
		if (!split_values(str, info))
			return (0);
		return (1);
	}
	return (1);
}

int	init_text_struct(char *str, t_gen_info *info)
{
	if (strcomp(str,"NO ") == 1)
	{
		info->texture_NO_path = ft_strdup(str + ft_strlen("NO "));
		if (!info->texture_NO_path)
			return (1);
	}
	else if (strcomp(str, "SO "))
	{
		info->texture_SO_path = ft_strdup(str + ft_strlen("SO "));
		if (!info->texture_SO_path)
			return (1);
	}
	else if (strcomp(str, "WE "))
	{
		info->texture_WE_path = ft_strdup(str + ft_strlen("WE "));
		if (!info->texture_WE_path)
			return (1);
	}
	else if (strcomp(str, "EA "))
	{
		info->texture_EA_path = ft_strdup(str + ft_strlen("EA "));
		if (!info->texture_EA_path)
			return (1);
	}
	return (0);
}

int get_max_len(char **str, t_gen_info *info)
{
	int len;
	int	i;

	i = 1;
	len = (int)ft_strlen(str[0]);
	while (str[i] != NULL)
	{ 
		if (len < (int)ft_strlen(str[i]))
			len = (int)ft_strlen(str[i]);
		i++;
	}
	info->map_y = i - 1;
	// printf("y: %d, str: %s\n", info->map_y, str[info->map_y]);
	return (len);
}

int set_to_map(t_gen_info *info, char **str)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	j = 0;
	x = 0;
	y = 0;
	printf("x length: %d\n", info->map_x);
	info->map = ft_calloc(info->map_y + 2, sizeof(char *));
	if (!info->map)
		error_free_exit("Error\nmalloc", info, INFO_STRING);
	while (str[i] != NULL)
	{
		j = 0;
		x = 0;
		info->map[y] = ft_calloc(info->map_x + 1, sizeof(char));
		if (!info->map[y])
			return (0);
		while (str[i][j] != 0 && str[i][j] != 10 && j < info->map_x)
		{
			ft_memset(&info->map[y][x], str[i][j], 1);
			// printf("x: %d: (%d -> %c) ", x, info->map[y][x], info->map[y][x]);
			// info->map[y][x] = str[i][j];
			j++;
			x++;
		}
		while (x < info->map_x)
		{

			info->map[y][x] = '1';
			// printf("x: %d: %c ", x, info->map[y][x]);
			x++;
		}
		info->map[y][x] = '\0';
		// info->map[y][x] = '1';
		// printf("map line: %s: size: %d index: %d\n", info->map[y], (int)ft_strlen(info->map[y]), y);
		// printf("%d\n", info->map_x);
		// info->map[y][info->map_x] = 0;
		
		// printf("size: %d\n: %s\n", (int)ft_strlen(info->map[y]), info->map[y]);
		// printf("%s\n", info->map[y]);
		i++;
		y++;
	}
	info->map[y] = NULL;
	printf("\n");
	return (1);
}

int	parse_data_info(t_gen_info *info)
{
	int	i;
	int	j;
	// int size;

	i = 0;
	j = 0;
	while (info->info_string[i] != NULL)
	//evtl while (info->info_string[i][0] != '\0')?
	{
		if (init_text_struct(info->info_string[i], info))
		{
			error_free_exit("Error\nmalloc", info, TEXTURE_PATH);
		}
		if (!parse_color_settings(info->info_string[i], info))
			return (0);
		if (map_parse_condition(info, i) == 1)
		{
			info->map_x = get_max_len(&info->info_string[i], info);		
			set_to_map(info, &info->info_string[i]);
			// set_to_map(info, &info->info_string[i]);
			// printf("max size: %d\n", info->map_x);
			break;
		}
		i++;
	}
	// while (info->map[j] != NULL)
	// {
	// 	printf("%s\n", info->map[j]);
	// 	j++;
	// }
	if (!info->floor.set || !info->ceiling.set)
	{
		printf("COLOR SETTING IS MISSING\n");
		return (0);
	}
	// printf("y: %d, map: %s\n", info->map_y, info->map[info->map_y]);
	if (check_map_valid(info) && map_base_player_check(info))
		return (1);
	// exit(0);
	error_free_exit("\033[31mMAP IS NOT VALID\033[0m", info, INFO_MAP);
	return (0);
}

int	init_data_info(t_gen_info *info, char *argv[], int argc)
{
	char	*line;
	int		i;

	if (argc == 1)
	{
		info->fd = open("scene.cub", O_RDONLY);
		if (info->fd == -1)
			error_exit("Error\nfiledescriptor", info);
	}
	else if (argc == 2 && check_file_format(argv[1]))
	{
		info->path = ft_strdup(argv[1]);
		info->fd = open(info->path, O_RDONLY);
		if (info->fd == -1)
			error_exit("Error\nfiledescriptor", info);
		return (0);// muss rausgenommen werden nur zum testen da
	}
	else if (argc == 2 && !check_file_format(argv[1]))
	{
		error_exit("Error\nfile extension is wrong!\n", info);
    	return (0);
  	}
	info->info_string = (char **)malloc(sizeof(char *) * 250);
	//hier noch eine Lösung überlegen, wie man die Größe bestimmt
	//eine simple zählfunktion, die lediglich die y-Achse der map zählt?
	if (!info->info_string)
		error_exit("Error\nmalloc", info);
	i = 0;
	line = get_next_line(info->fd);
	while (line)
	{
		info->info_string[i] = ft_strdup(line);
		if (!info->info_string[i])
			error_free_exit("Error\nmalloc",info, INFO_STRING);
		free(line);
		line = get_next_line(info->fd);
		// free(line);
		i++;
	}
	free(line);
	//hier noch eine Lösung überlegen, wie man die Größe bestimmt
	//eine simple zählfunktion, die lediglich die y-Achse der map zählt?
	if (parse_data_info(info))
		return (1);
	return (0);
}
//merge