//
// Created by Jaewook Kim on 4/29/22.
//

#include "ft_Cub3D.h"

void            location_init(t_location *location)
{
    location->x = 0;
    location->y = 0;
}

int             key_press(int keycode, t_location *location)
{
    if (keycode == KEY_W)
        location->y--;
    else if (keycode == KEY_A)
        location->x--;
    if (keycode == KEY_S)
        location->y++;
    else if (keycode == KEY_D)
        location->x++;
    else if (keycode == KEY_ESC)
        exit(0);
    printf("x: %d / y: %d\n", location->x, location->y);
    return (0);
}

int             close_win(int keycode, int x, int y, void *param)
{
    (void)keycode;
    (void)x;
    (void)y;
    (void)param;
    exit(0);
}

char **read_map(char *argv)
{
    int fd;
    char *tmp;
    int i;
    char **ret;
    fd = open(argv, O_RDONLY);
    if (fd < 0)
        printf("%s", "ERROR");
    i = 0;
    while ((get_next_line(fd, &tmp)))
    {
        free(tmp);
        i++;
    }
    free(tmp);
    ret = (char **)malloc(sizeof(char *) * (i + 2));
    close(fd);
    fd = open(argv, O_RDONLY);
    if (fd < 0)
        printf("%s", "ERROR");
    i = 0;
    while ((get_next_line(fd, &ret[i])))
        i++;
    ret[++i] = 0;
    //testcode : print readed map
    for (int j = 0; j < 5; j++)
        printf("%s\n", ret[j]);
    return (ret);
}

void    *

int main(int ac, char *av[])
{
    void *mlx;
    void *win;
    t_location location;
    t_data data;
    if (argc != 2)
        return 1;
    // if (argv[1] == .cub파일)
    data.map = read_map(argv[1]);

    location_init(&location);
    mlx = mlx_init();
    win = mlx_new_window(mlx, 500, 500, "cub3D");
    data.img_ptr = mlx_png_file_to_image(mlx, "../pics/eagle.png", 500, 500);
    mlx_hook(win, EVENT_KEY_PRESS, 0, &key_press, &location);
    mlx_hook(win, CLICK_RED_BUTTON, 0, &close_win, 0);
    mlx_string_put (mlx, win, 0, 0, 16711680, "string");
    mlx_loop(mlx);
    return 0;
}