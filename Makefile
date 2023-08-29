NAME			=	miniRT

# **************************** COMPILER SETTINGS ***************************** #

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -MMD -MP
CPPFLAGS		=	-I./include
LDFLAGS			=
LDLIBS			=	

# ********************************* LIBRAY *********************************** #

# libft
LIBFT_PATH		=	./lib/libft
LDFLAGS			+=	-L./${LIBFT_PATH}
LDLIBS			+=	-lft

# libstr
LIBSTR_PATH		=	./lib/libstr
LDFLAGS			+=	-L./${LIBSTR_PATH}
LDLIBS			+=	-lstr

# libmlx
LIBMLX_PATH		=	./lib/libmlx
LDFLAGS			+=	-L./${LIBMLX_PATH}
LDLIBS			+=	-lmlx

# libmlx
LIBMLX_PATH		=	./lib/libmath
LDFLAGS			+=	-L./${LIBMATH_PATH}
LDLIBS			+=	-lmath

# ****************************** SOURCE FILES ******************************** #

SRCS 			=	$(wildcard src/*.c)
OBJS			=	$(SRCS:.c=.o)
DEPS			=	$(SRCS:.c=.d)

# ********************************** RULES ********************************** #

all:
	make -C $(LIBFT_PATH) --silent
	make -C $(LIBSTR_PATH) --silent
	make -C $(LIBMLX_PATH) --silent
	make $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) $^ -o $@

clean:
	make -C $(LIBFT_PATH) clean --silent
	make -C $(LIBSTR_PATH) clean --silent
	make -C $(LIBMLX_PATH) clean --silent
	rm -f $(OBJS) $(DEPS)

fclean:
	make -C $(LIBFT_PATH) fclean --silent
	make -C $(LIBSTR_PATH) fclean --silent
	make -C $(LIBMLX_PATH) clean --silent
	rm -f $(NAME) $(OBJS) $(DEPS)

re: 
	make fclean
	make all

.PHONY: all clean fclean re
