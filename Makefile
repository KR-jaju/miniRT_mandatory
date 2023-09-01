NAME			=	miniRT

# **************************** COMPILER SETTINGS ***************************** #

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -MMD -MP
CPPFLAGS		=	-I./include -I./lib/include
LDFLAGS			=
LDLIBS			=	

# ********************************* LIBRAY *********************************** #

# libft
LIBFT_PATH		=	./lib/libft
LDFLAGS			+=	-L./${LIBFT_PATH}
LDLIBS			+=	-lft -lftprintf -lgnl

# libstr
LIBSTR_PATH		=	./lib/libstr
LDFLAGS			+=	-L./${LIBSTR_PATH}
LDLIBS			+=	-lstr

# libds
LIBDS_PATH		=	./lib/libds
LDFLAGS			+=	-L./${LIBDS_PATH}
LDLIBS			+=	-lds

# libmlx
LIBMLX_PATH		=	./lib/libmlx
LDFLAGS			+=	-L./${LIBMLX_PATH}
LDLIBS			+=	-lmlx

# libmath
LIBMATH_PATH	=	./lib/libmath
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
	make -C $(LIBDS_PATH) --silent
# make -C $(LIBMLX_PATH) --silent
	make -C $(LIBMATH_PATH) --silent
	make $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	make -C $(LIBFT_PATH) clean --silent
	make -C $(LIBSTR_PATH) clean --silent
	make -C $(LIBDS_PATH) clean --silent
# make -C $(LIBMLX_PATH) clean --silent
	make -C $(LIBMATH_PATH) clean --silent
	rm -f $(OBJS) $(DEPS)

fclean:
	make -C $(LIBFT_PATH) fclean --silent
	make -C $(LIBSTR_PATH) fclean --silent
	make -C $(LIBDS_PATH) fclean --silent
# make -C $(LIBMLX_PATH) clean --silent
	make -C $(LIBMATH_PATH) fclean --silent
	rm -f $(NAME) $(OBJS) $(DEPS)

re: 
	make fclean
	make all

.PHONY: all clean fclean re
