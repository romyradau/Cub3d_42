
#ifndef CUB3D_H
# define CUB3D_H


# include "libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define WINDOW_X 850
# define WINDOW_Y 850
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_ESC 53
# define RIGHT 124
# define DOWN 125

typedef enum free_code{
	INFO_STRING,
	TEXTURE_PATH,
	INFO_MAP,
}	t_free_code;
//new

typedef struct s_point
{
	int		x;
	int		y;
}t_point;

typedef struct s_player
{
	t_point		p_pos;
	int			dis_to_wall;
	char 		*looking;
}t_player;

typedef struct s_color
{
	int red;
	int yellow;
	int blue;
	
}t_color;

typedef struct s_gen_info
{
	t_player 	*player;
	int			map_x;
	int			map_y;
	int			map_height;
	int			map_widht;
	int			fd;
	t_color		ceiling;
	t_color		floor;
	char		*path;
	char 		**map;
	char		*texture_NO_path;
	char		*texture_SO_path;
	char		*texture_WE_path;
	char		*texture_EA_path;
	char		**info_string;
}t_gen_info;

typedef struct s_window_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_lenght;
	int endian;
}t_window_data;

/********************WINDOW_MLX***************************/
void create_window(void);

/********************STIRNG_TOOLS************************/
char *ft_strchr_nl(char *str);
void split_values(char *str, t_gen_info *info);
int strcomp(char *str1, const char *str2);
/*****************READ_TOOLS****************************/
char *get_next_line(int fd);
int check_map_valid(t_gen_info *info);
int map_base_player_check(t_gen_info *info);
int check_file_format(char *argv[]);
int init_data_info(t_gen_info *info, char *argv[], int argc);


void create_window(void);

/*****************ERROR****************************/
void    error_exit(char *str, t_gen_info *info);
void    error_free_exit(char *str, t_gen_info *info, int i);


#endif