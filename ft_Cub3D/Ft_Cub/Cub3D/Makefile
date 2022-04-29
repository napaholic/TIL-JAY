NAME = cub3D

CC = gcc
CFLAGS = -Wall -Wextra -Werror
MFLAGS = -L ./mlx -lmlx -framework OpenGL -framework AppKit

SRCS = ft_Cub3D.c ../gnl/get_next_line.c ../gnl/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

BONUS = ./bonus_dir

all: $(NAME)

%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(MFLAGS)

bonus:
	make all -C $(BONUS)

clean:
	rm -f $(OBJS)
	# make fclean -C $(BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
