NAME = fdf
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
INCLUDES = -I/home/fnasser/local/include -Ilibft -Ilibft/libftprintf
LIBRARY = -L/home/fnasser/local/lib -Llibft -Llibft/libftprintf
LIBRARIES = -lmlx -lXext -lX11 -lm -lz -lft -lftprintf
SRC = 	center.c draw.c free_utils.c get_min_max_z.c utils.c \
		handle_events.c main.c parse.c put_map.c wireframe.c \
		libft/gnl/get_next_line.c libft/gnl/get_next_line_utils.c
OBJ = $(SRC:.c=.o)
RM = rm -rf
%.o: %.c 
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
all: $(NAME)
$(NAME): $(OBJ) libft/libft.a libft/libftprintf/libftprintf.a
	$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) $(LIBRARY) $(LIBRARIES) \
	-o $(NAME)
libft/libft.a:
	make -C libft
clean:
	$(RM) $(OBJ)
	make clean -C libft
fclean: clean
	$(RM) $(NAME)
	make fclean -C libft
re: fclean all
bonus: all
.PHONY: all clean fclean re bonus
