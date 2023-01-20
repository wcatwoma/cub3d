COLORGREEN = \033[32m
COLORREED = \033[31m
COLORWHITE = \033[0m

NAME = cub3D
SRCS = ./cub3d.c ./tools/other.c \
		./tools/init.c \
		./tools/parser.c \
		./tools/free.c \
		./tools/checker.c \
		./tools/errors.c \
		./engine/run_game.c \
		./engine/drawing.c \
		./engine/math_field.c \
		./engine/math_ray.c \
		./engine/math_ray.c \
		./engine/math_func.c \
		./engine/math_func_2.c \
		./engine/drawing_sprite.c \
		./engine/drawing_line.c \
		./engine/motion.c \
		./engine/save_screen.c 
LIBFTDIR = ./tools/libft/
MINILIBXDIR = ./engine/minilibx/
LIBFT = $(LIBFTDIR)libft.a
MINILIBX = $(MINILIBXDIR)libmlx.a
FLAGS = -Wall -Wextra -Werror
FLAGSMLX = -framework OpenGL -framework AppKit
HEADER = ./cub3d.h
OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MINILIBX)
	@echo "$(COLORGREEN)Assembled object files!$(COLORWHITE)"
	@gcc -o $@ $^ $(FLAGSMLX)
	@echo "$(COLORGREEN)Assembled cub3D!$(COLORWHITE)"

%.o: %.c 
	@gcc $(FLAGS) -I $(HEADER) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFTDIR)
	@echo "$(COLORGREEN)Assembled libft.a!$(COLORWHITE)"

$(MINILIBX):
	@make -C $(MINILIBXDIR)
	@echo "$(COLORGREEN)Assembled libmlx.a!$(COLORWHITE)"

clean:
	@make clean -C $(LIBFTDIR)
	@make clean -C $(MINILIBXDIR)
	@rm -f *.o
	@rm -f ./tools/*.o
	@rm -f ./engine/*.o
	@echo "$(COLORREED)Deleted the object files.$(COLORWHITE)"

fclean: clean
	@make fclean -C $(LIBFTDIR)
	@echo "$(COLORREED)Deleted $(LIBFT).$(COLORWHITE)"
	@rm -f $(NAME)
	@echo "$(COLORREED)Deleted $(NAME).$(COLORWHITE)"

re: fclean all

.PHONY: all clean fclean re