NAME		=	cub3D

SRC			=	src
INC			=	include
OBJ			=	obj

LIB			=	lib
LIBFT		=	$(LIB)/libft
MLX_LINUX	=	$(LIB)/mlx_linux

CC			=	clang
CFLAGS		=	-Wall -Werror -Wextra -Wpedantic -Wfloat-conversion -Wsign-conversion

RM			=	rm -rf
MK			=	mkdir -p
NM			=	norminette

MAKE_DIR	= $(MAKE) --no-print-directory -C

CFILES		=	main.c buffer.c utils.c draw_line.c game.c draw_rect.c player.c\
				draw_circle.c event.c draw_ray.c draw_field.c draw_view.c\
				intersection.c parser.c parse_utils.c texture.c validate.c validate2.c\
				read_line.c read_line_utils.c error.c integrity.c world.c\
				draw_minimap.c

# Mandatory files which conflicts with bonuses
CMANDATORY	=	game_update.c

CBONUS		=	game_update_bonus.c

HFILES		=	buffer.h utils.h texture.h draw.h game.h player.h keymap.h event.h config.h\
				intersection.h world.h parser.h 

OFILES		=	$(CFILES:.c=.o)
OMANDATORY	=	$(CMANDATORY:.c=.o)
OBONUS		=	$(CBONUS:.c=.o)

SRCS		=	$(addprefix $(SRC)/, $(CFILES)) $(addprefix $(SRC)/, $(CMANDATORY)) $(addprefix $(SRC)/, $(CBONUS))
HEADERS		=	$(addprefix $(INC)/, $(HFILES))
OBJS		=	$(addprefix $(OBJ)/, $(OFILES))
OBJS_MAND	=	$(addprefix $(OBJ)/, $(OMANDATORY))
OBJS_BONUS	=	$(addprefix $(OBJ)/, $(OBONUS))

VPATH		=	$(SRC)

$(OBJ)/%.o:	%.c
			$(CC) $(CFLAGS) -I$(INC) -I$(LIB) -c $< -o $@

all:		$(NAME)

$(NAME):	CFLAGS += -O3 -DNDEBUG
$(NAME):	$(OBJ) $(OBJS) $(OBJS_MAND)
			@$(MAKE_DIR) $(LIBFT)
			$(CC) $(OBJS) $(OBJS_MAND) -L$(LIBFT) -lft -lmlx -lm -framework OpenGL -framework AppKit -o $(NAME)

$(OBJ):
			@$(MK) $(OBJ)

bonus:		CFLAGS += -O3 -DNDEBUG
bonus:		$(OBJ) $(OBJS) $(OBJS_BONUS)
			@$(MAKE_DIR) $(LIBFT)
			$(CC) $(OBJS) $(OBJS_BONUS) -L$(LIBFT) -lft -lmlx -lm -framework OpenGL -framework AppKit -o $(NAME)

debug:		CFLAGS += -g
debug:		$(OBJ) $(OBJS) $(OBJS_BONUS)
			@$(MAKE_DIR) $(LIBFT)
			$(CC) $(OBJS) $(OBJS_BONUS) -L$(LIBFT) -lft -lmlx -lm -framework OpenGL -framework AppKit -o $(NAME)

linux:		CFLAGS += -g
linux:		$(OBJ) $(OBJS) $(OBJS_BONUS)
			@$(MAKE_DIR) $(LIBFT)
			@$(MAKE_DIR) $(MLX_LINUX)
			$(CC) $(OBJS) $(OBJS_BONUS) -L$(LIBFT) -lft -L$(MLX_LINUX) -lmlx -lm -lXext -lX11 -o $(NAME)

clean:
#			@$(MAKE_DIR) $(LIBFT) clean
			@$(MAKE_DIR) $(MLX_LINUX) clean
			@$(RM) $(OBJS) $(OBJS_MAND) $(OBJS_MAND)

fclean:		clean
#			@$(MAKE_DIR) $(LIBFT) fclean
			@$(RM) $(NAME)

re:			fclean all

norme:
			@$(MAKE_DIR) $(LIBFT) norme
			@$(NM) $(SRCS) $(HEADERS)

.PHONY:		all debug clean fclean re norme linux bonus
